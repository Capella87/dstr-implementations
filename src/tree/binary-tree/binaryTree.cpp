#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "binaryTree.hpp"
#include <queue>

Node* get_node(const Data d)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;

    new_node->data = d;
    new_node->left = new_node->right = new_node->parent = NULL;

    return new_node;
}

Node* build_tree(Node* parent, Node* left, Node* right) // Build binary tree by 3 given nodes
{
    parent->left = left;
    if (left) left->parent = parent;

    parent->right = right;
    if (right) right->parent = parent;

    return parent;
}

int height(Node* n) // Returns the farthest distance from root to leaf node
{
    if (!n->left && !n->right) return 0;
    else if (n->left && !n->right) return 1 + height(n->left);
    else if (!n->left && n->right) return 1 + height(n->right);
    else return 1 + MAX(height(n->left), height(n->right));
}

bool is_root(Node* n) // Returns true if node n's parent is NULL
{
    return !n->parent ? true : false;
}

int depth(Node* n) // Returns distance from root to node n
{
    return is_root(n) ? 0 : 1 + depth(n->parent);
}

void preorder(Node* n)
{
    if (!n) return;

    printf("%d ", n->data);
    preorder(n->left);
    preorder(n->right);
}

void levelorder(Node* n)
{
    std::queue<Node*> q;
    q.push(n);

    while (!q.empty())
    {
        Node* t = q.front();

        printf("%d ", t->data);
        q.pop();
        if (t->left) q.push(t->left);
        if (t->right) q.push(t->right);
    }
    putchar('\n');
}

void inorder(Node* n)
{
    if (!n) return;

    inorder(n->left);
    printf("%d ", n->data);
    inorder(n->right);
}

void postorder(Node* n)
{
    if (!n) return;

    postorder(n->left);
    postorder(n->right);
    printf("%d ", n->data);
}

void free_all(Node* n)
{
    if (!n) return;

    free_all(n->left);
    free_all(n->right);
    free(n);
}

int main()
{
    Node* root = get_node(337);
    Node* a1 = get_node(284);
    Node* a2 = get_node(739);
    Node* a3 = get_node(402);
    Node* a4 = get_node(173);

    build_tree(root, a1, a2);
    build_tree(a1, NULL, a3);
    build_tree(a2, a4, NULL);

    printf("Preorder: ");
    preorder(root);
    putchar('\n');

    printf("Inorder: ");
    inorder(root);
    putchar('\n');

    printf("Postorder: ");
    postorder(root);
    putchar('\n');

    printf("Levelorder: ");
    levelorder(root);

    free_all(root);
    return 0;
}