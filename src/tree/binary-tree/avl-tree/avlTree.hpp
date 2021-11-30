#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <stdbool.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef int Data;
typedef struct _node
{
    Data data;
    struct _node* left;
    struct _node* right;
    int height;
} Node;

int height(const Node* n);
Node* get_node(const Data d);

Node* left_rotation(Node* n);
Node* right_rotation(Node* n);

int get_balance(const Node* n);
Node* min_node(Node* n);

Node* insert(Node* n, const Data d);
Node* detree(Node* n, const Data d);

void preorder_traversal(Node* n);
void inorder_traversal(Node* n);
void postorder_traversal(Node* n);
void levelorder_traversal(Node* n);

void free_all(Node* n);
#endif