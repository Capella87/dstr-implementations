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
    int data;
} node;

// Create a node and return it
node* creat_node(int data)
{
    node* rt = (node*)malloc(sizeof(node));
    rt->parent = rt->left = rt->right = (void*)0;
    rt->data = data;

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

// Get the sibling node of a node
node* sibling(node* n)
{
    if (!n->parent)
        return (void*)0;

    return n->parent->left == n ? n->parent->right : n->parent->left;
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

// Insert a new data
void insert(node** root, int data)
{
    node* target = search_tree(*root, data);

    // Exit the function if the data already exists
    if (target->data == data) return;

    // Transform the external node to internal node
    target->data = data;
    expand_external(target);
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