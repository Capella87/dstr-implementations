#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    struct node* left;
    struct node* right;
    struct node* parent;
    bool is_leaf;
    int data;
} node;

typedef struct tree
{
    node* root;
    node* last_node;
    int count;
} tree;

// Create and return a new node
node* creat_node(const int data, bool is_leaf)
{
    node* rt = (node*)malloc(sizeof(node));
    rt->left = rt->parent = rt->right = NULL;
    rt->data = data;
    rt->is_leaf = is_leaf;

    return rt;
}

// Initialize a tree
tree* init_tree(void)
{
    tree* rt = (tree*)malloc(sizeof(tree));
    rt->root = creat_node(0, true); // Create a leaf node
    rt->count = 0;
    rt->last_node = rt->root;

    return rt;
}

// Swap two elements
void swap(node* first, node* second)
{
    int temp = first->data;
    first->data = second->data;
    second->data = temp;
}

// Move a node up until reaching a proper place from the bottom
void up_heap(node* target)
{
    while (target->parent && target->parent->data < target->data)
    {
        swap(target->parent, target);
        target = target->parent;
    }
}

// Move a node down until reaching a proper place from the top
void down_heap(node* target)
{
    while (!target->is_leaf)
    {
        node* t = target;

        // Compare to the left child
        if (!target->left->is_leaf && target->left->data > t->data)
            t = target->left;

        // Compare to the right child
        if (!target->right->is_leaf && target->right->data > t->data)
            t = target->right;

        // Swap two values if the node has to be moved
        if (target != t)
        {
            swap(t, target);
            target = t;
        }
        else break;
    }
}

// Find the next location to be placed
// it is used after the new node is placed in the heap
node* find_location(tree* tree)
{
    node* pos = tree->last_node;

    // Move up until the node is left child of parent node
    while (pos->parent)
    {
        if (pos->parent->left == pos)
        {
            pos = pos->parent->right;
            break;
        }
        else pos = pos->parent;
    }

    // Move to left until a leaf node
    while (!pos->is_leaf && pos->left)
        pos = pos->left;

    return pos;
}

// Refresh the last node location
// it is used after the removal work
node* refresh_last_node(node* n, bool is_switched)
{
    node* pos = n;

    // Move up until the node is right child of parent node
    if (pos->parent && !is_switched)
    {
        if (pos->parent->right == pos) // Switch the direction
            pos = refresh_last_node(pos->parent->left, true);
        else if (pos->parent->left == pos)
            pos = refresh_last_node(pos->parent, is_switched);
    }
    else
    {
        // Move to right child until a leaf node
        if (pos->right && !pos->right->is_leaf)
            pos = refresh_last_node(pos->right, is_switched);
    }

    return pos;
}

// Insert an element to the heap
void insert(tree** tr, const int data)
{
    // Find location;
    node* location = find_location(*tr);
    // replace leaf node in the location to new node;
    node* new_elem = creat_node(data, false);
    new_elem->parent = location->parent;
    if (location->parent && location->parent->left == location)
        location->parent->left = new_elem;
    else if (location->parent && location->parent->right == location)
        location->parent->right = new_elem;
    else (*tr)->root = new_elem;

    location->parent = new_elem;
    new_elem->left = location;
    location = new_elem;

    // former leaf node to be left child of the new node and make right child leaf node.
    location->right = creat_node(0, true);
    location->right->parent = location;

    // refresh last_node;
    (*tr)->last_node = location;

    // Calibrate the heap
    (*tr)->count++;
    up_heap(location);
}

// Remove an element from the heap
int pop(tree** tr)
{
    if (!(*tr)->count)
    {
        printf("No element in the heap.");
        return -1;
    }

    int rt = (*tr)->root->data;

    if ((*tr)->root != (*tr)->last_node)
    {
        (*tr)->root->data = (*tr)->last_node->data;

        // Refresh last node information
        node* rem_target = (*tr)->last_node;
        (*tr)->last_node = refresh_last_node((*tr)->last_node, false);

        rem_target->left->parent = rem_target->parent;
        if (rem_target->parent && rem_target->parent->left == rem_target)
            rem_target->parent->left = rem_target->left;
        else if (rem_target->parent && rem_target->parent->right == rem_target)
            rem_target->parent->right = rem_target->left;

        // Remove last node and its right assistant node
        free(rem_target->right);
        free(rem_target);

        // DownHeap
        down_heap((*tr)->root);
    }
    else
    {
        node* empty_node = (*tr)->last_node->left;
        empty_node->parent = NULL;

        free((*tr)->last_node->right);
        free((*tr)->last_node);
        (*tr)->last_node = (*tr)->root = empty_node;
    }

    // Decrement count
    (*tr)->count--;

    return rt;
}

// Deallocate all nodes in the heap
void free_all_nodes(node* target)
{
    if (target->left)
        free_all_nodes(target->left);
    if (target->right)
        free_all_nodes(target->right);
    free(target);
}

// Release all resources of the heap
void free_all(tree* tr)
{
    free_all_nodes(tr->root);
    free(tr);
}

int main(void)
{
    tree* tr = init_tree();

    insert(&tr, 12);
    insert(&tr, 20);
    insert(&tr, 40);

    while (tr->count)
        printf("%d ", pop(&tr));
    putchar('\n');

    insert(&tr, 541);
    printf("%d\n", pop(&tr));

    free_all(tr);
    return 0;
}