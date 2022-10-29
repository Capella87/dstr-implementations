// 이진 탐색 트리 Binary Search Tree without external nodes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binarySearchTree.h"

node* creat_node(int data)
{
    node* rt = (node*)malloc(sizeof(node));
    rt->parent = rt->left = rt->right = NULL;
    rt->data = data;
    
    return rt;
}

void insert(node** root, node* parent, int data)
{
    if (!(*root))
    {
        (*root) = creat_node(data);
        (*root)->parent = parent;
        return;
    }

    if (data < (*root)->data) insert(&((*root)->left), *root, data);
    else if (data == (*root)->data) return;
    else insert(&((*root)->right), *root, data);
}

node* find_successor(node* n)
{
    while (n->left)
        n = n->left;
    return n;
}

int detree(node** root, node* parent, int target)
{
    if (!(*root)) return -1;

    if (target < (*root)->data)
        return detree(&((*root)->left), *root, target);
    else if ((*root)->data == target)
    {
        node* cur = (*root)->left;
        int data = (*root)->data;
        if (cur) cur = (*root)->right;

        if (!cur) // The node has only one child or no child
        {
            node* successor = (cur == (*root)->left) ? (*root)->right : (*root)->left;
            if (successor) successor->parent = (*root)->parent;
            free(*root);
            *root = successor;
        }
        else // The node has two children
        {
            node* successor = find_successor((*root)->right);
            (*root)->data = successor->data;
            
            if (successor->parent->left == successor)
                successor->parent->left = successor->right;
            else successor->parent->right = successor->right;
            if (successor->right) successor->right->parent = successor->parent;
            free(successor);
        }

        return data;
    }
    else return detree(&((*root)->right), *root, target);
}

void traversal(node* root, void (*method)(node*)) // function pointer
{
    method(root);
    putchar('\n');
}

void inorder(node* root)
{
    if (!root) return;

    if (root->left) inorder(root->left);
    printf("%d ", root->data);
    if (root->right) inorder(root->right);
}

void preorder(node* root)
{
    if (!root) return;

    printf("%d ", root->data);
    if (root->left) preorder(root->left);
    if (root->right) preorder(root->right);
}

void postorder(node* root)
{
    if (!root) return;

    if (root->left) postorder(root->left);
    if (root->right) postorder(root->right);
    printf("%d ", root->data);
}

void free_all(node* root)
{
    if (!root) return;

    if (root->left) free_all(root->left);
    if (root->right) free_all(root->right);
    free(root);
}

int main(void)
{
    node* root = NULL;

    insert(&root, NULL, 123);
    insert(&root, NULL, 87);
    insert(&root, NULL, 124);
    insert(&root, NULL, 523);
    traversal(root, inorder);

    detree(&root, NULL, 123);
    traversal(root, inorder);
    detree(&root, NULL, 2222);

    insert(&root, NULL, 89);
    insert(&root, NULL, 88);
    insert(&root, NULL, 91);
    traversal(root, inorder);
    detree(&root, NULL, 89);
    traversal(root, inorder);
    traversal(root, preorder);
    traversal(root, postorder);

    free_all(root);
    return 0;
}