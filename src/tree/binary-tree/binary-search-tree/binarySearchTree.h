#ifndef BINARYSEARCHTREE.H
#define BINARYSEARCHTREE_H

#include <stdbool.h>

typedef struct node
{
    struct node* parent;
    struct node* left;
    struct node* right;
    int data;
} node;

node* creat_node(int data);
void insert(node** root, node* parent, int data);
node* find_successor(node* n);
int detree(node** root, node* parent, int target);

void traversal(node* root, void (*method)(node*));
void inorder_traversal(node* root);
void preorder_traversal(node* root);
void postorder_traversal(node* root);

void free_all(node* root);

#endif