#include "binarySearchTree.hpp"
#include <iostream>
#include <queue>
using namespace std;

bool is_root(const Node* t) // 루트인 경우 true를 반환
{
    return !t->parent ? true : false;
}

Node* get_node(const Data d) // 노드 생성
{
    Node* n = new Node;
    n->d = d;
    n->left = n->right = n->parent = NULL;
    return n;
}


Node* insert(Node* root, Node* parent, const Data d) // 위치를 찾아 트리에 대입
{
    if (!root) // 해당 위치를 찾은 경우
    {
        Node* root = get_node(d);
        root->parent = parent;
        return root;
    }
    if (root->d < d) root->right = insert(root->right, root, d);
    else if (root->d > d) root->left = insert(root->left, root, d);
    return root;
}

Node* detree(Node* root, const Data t) // 대상을 찾아 트리에서 삭제
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
        Node* temp = min_node(root->right);
        root->d = temp->d;
        root->right = detree(root->right, temp->d);
    }
    return root;
}


int height(Node* root) // 트리 높이
{
    if (!root->left && !root->right) return 0;
    else if (root->left && !root->right) return 1 + height(root->left);
    else if (root->right && !root->left) return 1 + height(root->right);
    else return 1 + MAX(height(root->left), height(root->right));
}

int depth(Node* t) // 루트로부터 특정 노드 간의 거리인 '높이'
{
    return is_root(t) ? 0 : 1 + depth(t->parent);
}

Node* min_node(Node* t) // 삭제 대상 노드 자식들 중 가장 작은 노드를 찾는다.
{
    Node* cur = t;
    while (cur && cur->left)
        cur = cur->left;
    return cur;
}


void inorder(Node* t) // 중위 순회
{
    if (!t) return;
    if (t->left) inorder(t->left);
    printf("%d ", t->d);
    if (t->right) inorder(t->right);
    return;
}

void level_order(Node* t) // 레벨 순회 (루트부터 뿌리순으로 순회)
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


Node* search(Node* root, const Data t) // 대상을 찾는다. 없는 경우 NULL을 반환
{
    if (!root) return root;

    if (t < root->d) return search(root->left, t);
    else if (t > root->d) return search(root->right, t);
    return root;
}


void free_all(Node* root) // 종료 전 모든 노드 공간 반환
{
    if (!root) return;

    if (root->left) free_all(root->left);
    if (root->right) free_all(root->right);
    free(root);
    return;
}