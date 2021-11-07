#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./_common_/common.h"

// Make a simplified binary search tree

typedef struct _node
{
    int data;
    struct _node* left;
    struct _node* right;
    int count;
} Node;

Node* get_node(const int d)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = d;
    newNode->left = newNode->right = NULL;
    newNode->count = 1;
    return newNode;
}

Node* insert(Node* root, const int d) // Put data into tree.
{
    if (!root)
    {
        root = get_node(d);
        return root;
    }

    if (root->data > d) root->left = insert(root->left, d);
    else if (root->data < d) root->right = insert(root->right, d);
    else root->count++;
    return root;
}

void print_tree(Node* root) // Print all elements in the binary search tree.
{
    if (!root) return;

    print_tree(root->left);
    for (int i = 0; i < root->count; i++)
        printf("%d ", root->data);
    print_tree(root->right);
    return;
}

void free_all(Node* root) // Deallocate memory before the end of program.
{
    if (!root) return;

    if (root->left) free_all(root->left);
    if (root->right) free_all(root->right);
    free(root);
    return;
}

int main(void)
{
    int n;
    Node* t = NULL;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        t = insert(t, arr[i]);
    }
    print_array(arr, n);
    print_tree(t);

    free_all(t);
    free(arr);
    return 0;
}

/*
Input:
5
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
*/