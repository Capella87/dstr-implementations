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

bool isRoot(const Node* t);
Node* getNode(const Data d);
Node* insert(Node* root, Node* parent, const Data d);
int height(Node* root);
int depth(Node* t);
Node* minValueNode(Node* t);
Node* detree(Node* root, const Data t);
void inOrderTraverse(Node* t);
void levelOrderTraverse(Node* t);
Node* search(Node* root, const Data t);
void removeAll(Node* root);
#endif