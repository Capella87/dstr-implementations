#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// Node definition
typedef struct node
{
    struct node* parent;
    struct node* left;
    struct node* right;
    int height;
    int data;
} node;

// Create a node and return it
node* creat_node(int data)
{
    node* rt = (node*)malloc(sizeof(node));
    rt->parent = rt->left = rt->right = (void*)0;
    rt->data = data;
    rt->height = 0;

    return rt;
}

// Create two external nodes
void expand_external(node* n)
{
    if (!n) return;

    n->left = creat_node(-1);
    n->right = creat_node(-1);
    n->left->parent = n->right->parent = n;
}

// Get the height of node
int get_height(node* target)
{
    return !target ? 0 : target->height;
}

// Get a balance index by subtraction
int get_diff(node* n)
{
    if (!n) return 0;

    return get_height(n->left) - get_height(n->right);
}

// Return whether the node is balanced or not
bool is_balanced(node* n)
{
    if (!n) return false;

    int diff = get_diff(n);

    return diff < -1 || diff > 1 ? false : true;
}

// Return true if the node is an external node
bool is_external(node* n)
{
    if (!n) return false;

    return !n->left && !n->right ? true : false;
}

// Return true if the node is an internal node
bool is_internal(node* n)
{
    if (!n) return false;

    return n->left || n->right ? true : false;
}

// Update the height of node
bool update_height(node* n)
{
    if (!n) return false;

    int orig = n->height;
    n->height = 1 + MAX(get_height(n->left), get_height(n->right));
    return orig == n->height ? false : true;
}

// Get the sibling node of a node
node* sibling(node* n)
{
    if (!n->parent)
        return (void*)0;

    return n->parent->left == n ? n->parent->right : n->parent->left;
}

// Make child node a root node by right rotation
node* right_rotation(node* target, node* child)
{
    // To update child information for the parent node of target
    int direction = -1;
    // The direction variable will 1 if the right node of parent is the target
    if (target->parent)
        direction = target->parent->right == target ? 1 : 0;

    // Rotation
    node* child_right = child->right;
    child->right = target;
    child->parent = target->parent;
    target->parent = child;
        
    target->left = child_right;
    child_right->parent = target;

    // Update height information
    update_height(target);
    update_height(child);

    // Update the child information for the parent
    switch (direction)
    {
    case 1:
        child->parent->right = child;
        break;
    case 0:
        child->parent->left = child;
        break;
    }

    return child;
}

// Make child node a root node by right rotation
node* left_rotation(node* target, node* child)
{
    // To update child information for the parent node of target
    int direction = -1;
    // The direction variable will 1 if the right node of parent is the target
    if (target->parent)
        direction = target->parent->right == target ? 1 : 0;

    // Rotation
    node* child_left = child->left;
    child->left = target;
    child->parent = target->parent;
    target->parent = child;

    target->right = child_left;
    child_left->parent = target;

    // Update height information
    update_height(target);
    update_height(child);

    // Update the child information for the parent
    switch (direction)
    {
    case 1:
        child->parent->right = child;
        break;
    case 0:
        child->parent->left = child;
        break;
    }

    return child;
}

// Rebalance the tree
node* restructure(node* target, node* child, node* grand_child)
{
    //    (target)
    //      /
    //   (child)
    if (child->data < target->data)
    {
        //    (target)
        //      /
        //   (child)
        //    /
        // (grand_child)
        if (grand_child->data < child->data)
            return right_rotation(target, child);
        //    (target)
        //      /
        //   (child)
        //       \
        //    (grand_child)
        else
        {
            target->left = left_rotation(child, grand_child);
            return right_rotation(target, target->left);
        }
    }

    // (target)
    //   \
    //   (child)
    else
    {
        // (target)
        //   \
        //   (child)
        //      \
        //     (grand_child)
        if (child->data < grand_child->data)
            return left_rotation(target, child);

        // (target)
        //   \
        //   (child)
        //     /
        // (grand_child)
        else
        {
            target->right = right_rotation(child, grand_child);
            return left_rotation(target, target->right);
        }
    }
}

// Find a suitable position for the data
node* search_tree(node* n, int data)
{
    // Returns the external node when it finds the place to put (Precisely it reached to the end of the tree)
    if (is_external(n)) return n;

    if (data < n->data) return search_tree(n->left, data); // Recurse; Move to a left child
    else if (data == n->data) return n; // Returns the duplicate node when data is already put
    else return search_tree(n->right, data); // Recurse; Move to a right child
}

// Search the imbalance and fix them from the bottom
void insertion_inspector(node** root, node* target)
{
    node* pos = target;

    // Start an inspection from the new node;
    while (pos)
    {
        update_height(pos);

        if (pos->parent == (void*)0) *root = pos; // When pos reached the root node, update the pointer variable of root
        if (!is_balanced(pos)) break; // Exit the loop when an imbalance is detected. it only works the depth of the tree is bigger or equal than 3
        pos = pos->parent; // Move to the parent node
    }
    if (!pos) return; // Exit the function; it means there's no imbalance

    // Preparing to fix the found imbalance
    int diff = get_diff(pos);
    node* child = diff < -1 ? pos->right : pos->left;
    int second_diff = get_diff(child);
    
    // Prioritize less rotation
    node* grand_child;
    if (child == pos->left)
        grand_child = second_diff >= 0 ? child->left : child->right;
    else
        grand_child = second_diff <= 0 ? child->right : child->left;

    // Fix
    pos = restructure(pos, child, grand_child);
    // Update height information of remainder nodes from the pos to the root
    while (pos)
    {
        update_height(pos);
        if (pos->parent == (void*)0) *root = pos;
        pos = pos->parent;
    }
}

// Search the imbalance and fix them from the bottom after removal; Similar to detree_inspector
void detree_inspector(node** root, node* target)
{
    node* pos = target;

    // Start an inspection from the new node;
    while (pos)
    {
        update_height(pos);

        if (pos->parent == (void*)0) *root = pos; // When pos reached the root node, update the pointer variable of root
        if (!is_balanced(pos)) // Exit the loop when an imbalance is detected. it only works the depth of the tree is bigger or equal than 3
        {
            // Preparing to fix the found imbalance
            int diff = get_diff(pos);
            node* child = diff < -1 ? pos->right : pos->left;
            int second_diff = get_diff(child);

            // Prioritize less rotation
            node* grand_child;
            if (child == pos->left)
                grand_child = second_diff >= 0 ? child->left : child->right;
            else
                grand_child = second_diff <= 0 ? child->right : child->left;

            // Fix
            pos = restructure(pos, child, grand_child);
            if (!pos->parent) *root = pos; // Update *root information if updated pos is root
        }
        pos = pos->parent; // Move to the parent node
    }
    // Exit the function; it means there's no imbalance
}

// Insert a new data
void insert(node** root, int data)
{
    node* target = search_tree(*root, data);

    // Exit the function if the data already exists
    if (target->data == data) return;

    // Transform the external node to internal node
    target->data = data;
    target->height = 1;
    expand_external(target);

    // 'Maintenance'
    insertion_inspector(root, target);
    return;
}

// Find a data in the tree
int find_data(node* n, int data)
{
    // Not found
    if (is_external(n))
    {
        puts("X");
        return -1;
    }

    // Use recursion
    if (data < n->data)
        return find_data(n->left, data);
    // Print the data if it exists
    else if (data == n->data)
    {
        printf("%d\n", data);
        return data;
    }
    else return find_data(n->right, data);
}

// Remove an external node which is no longer needed
void reduce_external(node** parent, node* external, node** root)
{
    node* ano = sibling(external); // Use sibling node to replace the position

    if (!(*parent)->parent) // In case of root node
    {
        *root = ano;
        (*root)->parent = (void*)0;
    }
    else
    {
        node** pparent = &((*parent)->parent); // To preserve modifications
        ano->parent = *pparent; // Set sibling's new parent because the old parent will be removed
        if (*parent == (*pparent)->left) // Update *pparent child information
            (*pparent)->left = ano;
        else
            (*pparent)->right = ano;
    }

    // Remove an external node and the targeted node to be deleted
    free(*parent);
    free(external);
}

// Find the next successor of the deleted element
node* find_successor(node* n)
{
    while (is_internal(n->left))
        n = n->left;
    return n;
}

// Remove an element from the data if it is found
int detree(node** root, int data)
{
    node* n = search_tree(*root, data);

    if (is_external(n))
    {
        puts("X");
        return -1;
    }

    int e = n->data;

    node* begin = (void*)0; // A pointer variable for maintenance
    node* t = n->left;
    if (!is_external(t))
        t = n->right;
    if (is_external(t)) // In case of no children or only one child
    {
        begin = n->parent;
        reduce_external(&n, t, root);
    }
    else // In case of two children
    {
        node* successor = find_successor(n->right); // Find a successor for the vacant node
        t = successor->left;

        node** nn = &n; // To preserve modifications
        (*nn)->data = successor->data;
        begin = successor->parent;
        reduce_external(&successor, t, root); // Remove obsolete original successor node
    }
    printf("%d\n", e);

    detree_inspector(root, begin); // Fix imbalance in the tree
    return e;
}

// Free all elements in the tree before the termination
void free_all(node* n)
{
    if (!n) return;

    if (n->left) free_all(n->left);
    if (n->right) free_all(n->right);
    free(n);
}

// Traverse a tree and show its elements
void traversal(node* n, void (*way)(node*))
{
    way(n);
    putchar('\n');
}

// Preorder traversal
void preorder(node* n)
{
    if (is_external(n))
        return;

    printf("%d ", n->data);
    if (!is_external(n->left))
        preorder(n->left);
    if (!is_external(n->right))
        preorder(n->right);
}

// Inorder traversal
void inorder(node* n)
{
    if (is_external(n))
        return;
    
    if (!is_external(n->left))
        inorder(n->left);
    printf("%d ", n->data);
    if (!is_external(n->right))
        inorder(n->right);
}

// Inorder traversal
void postorder(node* n)
{
    if (is_external(n))
        return;
    
    if (!is_external(n->left))
        postorder(n->left);
    if (!is_external(n->right))
        postorder(n->right);
    printf("%d ", n->data);
}

// Driver code
int main(void)
{
    char command;
    int data;
    node* root = creat_node(-1);

    while (1)
    {
        command = getchar();

        // Quit
        if (command == 'q') break;
        getchar();
        switch (command)
        {
        // Insertion
        case 'i':
            scanf("%d", &data);
            getchar();

            insert(&root, data);
            break;

        // Remove a data from the tree
        case 'd':
            scanf("%d", &data);
            getchar();

            detree(&root, data);
            break;

        // Search a data from the tree
        case 's':
            scanf("%d", &data);
            getchar();

            find_data(root, data);
            break;

        // Print all elements in the tree
        case 'p':
            traversal(root, preorder);
            break;
        }
    }

    free_all(root);
    return 0;
}