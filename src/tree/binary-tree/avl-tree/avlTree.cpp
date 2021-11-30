#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <queue>
#include "avlTree.hpp"

int height(const Node* n)
{
    return !n ? 0 : n->height;
}

Node* get_node(const Data d)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;

    new_node->data = d;
    new_node->left = new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

/*
* Left Rotation
        [n]                [t]
       //  \               / \\
      (a)  [t]    ==>    [n]  (c)
          // \\         // \\
         (b) (c)       (a) (b)
*/

Node* left_rotation(Node* n)
{
    Node* t = n->right;
    Node* temp = t->left;

    t->left = n;
    n->right = temp;

    // Update heights
    n->height = 1 + MAX(height(n->left), height(n->right));
    t->height = 1 + MAX(height(t->left), height(t->right));

    return t;
}

/*
* Right Rotation
        [n]                [t]
        / \\              //  \
      [t]  (c)   ==>     (a)  [n]
     // \\                   // \\
    (a) (b)                 (b)  (c)
*/

Node* right_rotation(Node* n)
{
    Node* t = n->left;
    Node* temp = t->right;

    t->right = n;
    n->left = temp;

    // Update heights
    n->height = 1 + MAX(height(n->left), height(n->right));
    t->height = 1 + MAX(height(t->left), height(t->right));
    
    return t;
}

int get_balance(const Node* n)
{
    return !n ? 0 : height(n->left) - height(n->right);
}

Node* insert(Node* n, const Data d)
{
    if (!n)
    {
        n = get_node(d);
        if (!n) exit(EXIT_FAILURE);
        return n;
    }
    
    if (d < n->data)
        n->left = insert(n->left, d);
    else if (n->data < d)
        n->right = insert(n->right, d);
    else return n;

    n->height = 1 + MAX(height(n->left), height(n->right));
    int balance = get_balance(n);

    if (balance > 1 && d < n->left->data)
        return right_rotation(n);
    else if (balance > 1 && n->left->data < d)
    {
        n->left = left_rotation(n->left);
        return right_rotation(n);
    }
    else if (balance < -1 && d < n->right->data)
    {
        n->right = right_rotation(n->right);
        return left_rotation(n);
    }
    else if (balance < -1 && n->right->data < d)
        return left_rotation(n);

    return n;
}

Node* min_node(Node* n)
{
    Node* cur = n;
    while (cur->left)
        cur = cur->left;

    return cur;
}

Node* detree(Node* n, const Data d)
{
    if (!n) return n;

    // Find 'd' node
    if (d < n->data)
        n->left = detree(n->left, d);
    else if (n->data < d)
        n->right = detree(n->right, d);
    else
    {
        if (!n->left || !n->right)
        {
            Node* temp = n->left ? n->left : n->right;
            if (!temp) // NULL both
            {
                temp = n;
                n = NULL;
            }
            else *n = *temp; // Move child value to old n node
            free(temp);
        }
        else // two children
        {
            Node* temp = min_node(n->right);
            n->data = temp->data;
            n->right = detree(n->right, temp->data);
        }
    }

    if (!n) return n;
    
    // Update height
    n->height = 1 + MAX(height(n->left), height(n->right));
    
    // Update balance
    int balance = get_balance(n);

    int left_balance = get_balance(n->left);
    if (balance > 1 && left_balance >= 0)
        return right_rotation(n);
    else if (balance > 1 && left_balance < 0)
    {
        n->left = left_rotation(n->left);
        return right_rotation(n);
    }

    int right_balance = get_balance(n->right);
    if (balance < -1 && right_balance > 0)
    {
        n->right = right_rotation(n->right);
        return left_rotation(n);
    }
    else if (balance < -1 && right_balance <= 0)
        return left_rotation(n);

    return n;
}

void inorder_traversal(Node* n)
{
    if (!n) return;

    inorder_traversal(n->left);
    printf("%d ", n->data);
    inorder_traversal(n->right);
}

void preorder_traversal(Node* n)
{
    if (!n) return;

    printf("%d ", n->data);
    preorder_traversal(n->left);
    preorder_traversal(n->right);
}

void postorder_traversal(Node* n)
{
    if (!n) return;

    postorder_traversal(n->left);
    postorder_traversal(n->right);
    printf("%d ", n->data);
}

void levelorder_traversal(Node* n)
{
    if (!n) return;

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

void free_all(Node* n)
{
    if (!n) return;

    free_all(n->left);
    free_all(n->right);
    free(n);
}


int main()
{
    Node* root = NULL;

    root = insert(root, 123);
    root = insert(root, 129);
    root = insert(root, 423);
    root = insert(root, 3);
    root = insert(root, 12);
    root = insert(root, 124);
    root = insert(root, 122);

    printf("Preorder: ");
    preorder_traversal(root);
    putchar('\n');

    printf("Levelorder: ");
    levelorder_traversal(root);

    root = detree(root, 423);
    root = detree(root, 124);
    root = detree(root, 129);

    printf("Preorder: ");
    preorder_traversal(root);
    putchar('\n');

    printf("Levelorder: ");
    levelorder_traversal(root);

    free_all(root);
    return 0;
}