#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef int Data;

typedef struct _node
{
    Data d;
    struct _node* left;
    struct _node* right;
    struct _node* parent;
} Node;

bool is_root(const Node* t);
Node* get_node(const Data d);

Node* insert(Node* root, Node* parent, const Data d);
Node* detree(Node* root, const Data t);

int height(Node* root);
int depth(Node* t);
Node* min_node(Node* t);

void inorder(Node* t);
void level_order(Node* t);

Node* search(Node* root, const Data t);

void free_all(Node* root);
#endif