#include "binarySearchTree.hpp"
#include <iostream>
#include <queue>
using namespace std;

bool isRoot(const Node* t)
{
    return !t->parent ? true : false;
}

Node* getNode(const Data d)
{
    Node* newNode = new Node;
    newNode->d = d;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

Node* insert(Node* root, Node* parent, const Data d)
{
    if (!root) // 해당 위치를 찾은 경우
    {
        Node* root = getNode(d);
        root->parent = parent;
        return root;
    }
    if (root->d < d) root->right = insert(root->right, root, d);
    else if (root->d > d) root->left = insert(root->left, root, d);
    return root;
}

int height(Node* root)
{
    if (!root->left && !root->right) return 0;
    else if (root->left && !root->right) return 1 + height(root->left);
    else if (root->right && !root->left) return 1 + height(root->right);
    else return 1 + MAX(height(root->left), height(root->right));
}

int depth(Node* t)
{
    return isRoot(t) ? 0 : 1 + depth(t->parent);
}

Node* minValueNode(Node* t)
{
    Node* cur = t;
    while (cur && cur->left) // !
        cur = cur->left;
    return cur;
}

Node* detree(Node* root, const Data t)
{
    if (!root) return root;

    if (root->d > t) root->left = detree(root->left, t);
    else if (root->d < t) root->right = detree(root->right, t);
    else
    {
        if (!root->left)  // Right child만 존재하는 경우
        {
            Node* temp = root->right;
            if (temp) temp->parent = root->parent;
            free(root);
            return temp;
        }
        else if (!root->right) // Left child만 존재하는 경우
        {
            Node* temp = root->left;
            if (temp) temp->parent = root->parent;
            free(root);
            return temp;
        }
        // 둘 다 있는 경우
        Node* temp = minValueNode(root->right);
        root->d = temp->d;
        root->right = detree(root->right, t);
    }
    return root;
}

void inOrderTraverse(Node* t)
{
    if (!t) return;
    if (t->left) inOrderTraverse(t->left);
    printf("%d ", t->d);
    if (t->right) inOrderTraverse(t->right);
    return;
}

void levelOrderTraverse(Node* t)
{
    queue<Node*> q;
    q.push(t);
    while (!q.empty())
    {
        Node* cur = q.front();
        q.pop();
        printf("%d ", cur->d);
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    cout << '\n';
    return;
}

Node* search(Node* root, const Data t)
{
    if (!root) return root;

    if (t < root->d) return search(root->left, t);
    else if (t > root->d) return search(root->right, t);
    return root;
}

void removeAll(Node* root)
{
    if (!root) return;

    if (root->left) removeAll(root->left);
    if (root->right) removeAll(root->right);
    free(root);
    return;
}