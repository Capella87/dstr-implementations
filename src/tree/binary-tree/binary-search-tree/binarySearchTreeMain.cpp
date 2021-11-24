#include "binarySearchTree.hpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    Node* root = NULL;
    const int KEYWORD = 2;

    root = insert(root, NULL, 123);
    insert(root, NULL, 88);
    insert(root, NULL, 2);
    insert(root, NULL, 905);
    insert(root, NULL, 972);
    insert(root, NULL, 376);
    insert(root, NULL, 9);
    insert(root, NULL, 649);
    insert(root, NULL, 693);
    insert(root, NULL, 529);
    insert(root, NULL, 784);
    insert(root, NULL, 523);
    
    inorder(root);
    cout << '\n';
    level_order(root);
    cout << "Depth of " << KEYWORD << " : " << depth(search(root, KEYWORD)) << '\n';
    cout << "Heights of tree: " << height(root) << '\n';
    detree(root, KEYWORD);
    inorder(root);
    cout << '\n';
    if (!search(root, KEYWORD)) cout << KEYWORD << " is NOT exist in tree.\n";
    else cout << KEYWORD << " is exist in tree.\n";
    
    free_all(root);
    return 0;
}