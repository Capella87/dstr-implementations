#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <stdbool.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef int Data;
typedef struct _node
{
    Data data;
    struct _node* left;
    struct _node* right;
    struct _node* parent;
} Node;

Node* get_node(const Data d);
Node* build_tree(Node* parent, Node* left, Node* right);
int height(Node* n);
int depth(Node* n);
bool is_root(Node* n);

void preorder(Node* n);
void levelorder(Node* n);
void inorder(Node* n);
void postorder(Node* n);

void free_all(Node* n);

#endif