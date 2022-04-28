#include <iostream>
#include <string>
#include <cmath>
#include "BST.hpp"
#include "BST.cpp"
using namespace std;

// [optional] function for printing trees:
struct Trunk
{
    Trunk *prev;
    string str;
    Trunk(Trunk *prev, const string &str)
        : prev(prev), str(str) {}
};
// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;
    showTrunks(p->prev);
    printf("%s", p->str.c_str());
}
void printTree(const BSTNode<int> *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
    printTree(root->right, trunk, true);

    if (prev == nullptr)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }
    showTrunks(trunk);
    printf("%d\n", root->data);

    if (prev != nullptr)
        prev->str = prev_str;

    trunk->str = "   |";
    printTree(root->left, trunk, false);
    delete trunk;
}

int main()
{
    int x;
    cin >> x;
    puts("---------------------------------------------------------");
    BST<int> tree;

    int a[] = {69, 3, 66, 7, 2, 44, 98, 12, 13, 9, 100, 99, 200};
    const int n = sizeof(a) / sizeof(int);

    for (int i = 0; i < n; i++)
        tree.insert(a[i]);

    printTree(tree.getRoot(), nullptr, false);
    puts("");

    for (int i = 0; i < n; i++)
    {
        cout << "Deleting " << a[i] << endl;
        tree.deleteNode(a[i]);
        printTree(tree.getRoot(), nullptr, false);
        puts("");
    }
    return 0;
}