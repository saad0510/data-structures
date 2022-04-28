#include <iostream>
#include <string>
#include <cmath>
#include "BST.hpp"
#include "BST.cpp"
using namespace std;

struct Trunk;
void printTree(const BSTNode<int> *root, Trunk *prev = nullptr, bool isLeft = false);

template <typename T>
inline void BST<T>::makeBackBone()
{
    root = makeBackBoneUtil(root);
}

template <typename T>
inline BSTNode<T> *BST<T>::makeBackBoneUtil(Node *node)
{
    if (node == nullptr)
        return node;
    node->left = makeBackBoneUtil(node->left);

    if (node->left != nullptr)
        node = rotateRight(node);

    node->right = makeBackBoneUtil(node->right);
    return node;
}

template <typename T>
inline int BST<T>::getBalanceNodes(const int total_nodes) const
{
    int level = 1;
    int nodes = 0;
    for (int i = 1; i <= total_nodes; i++)
        if (i == pow(2, level) - 1)
        {
            level++;
            nodes = i;
        }
    return nodes;
}

template <typename T>
inline void BST<T>::balanceTree(const int total_nodes)
{
    const int balanced_nodes = getBalanceNodes(total_nodes);
    int difference = total_nodes - balanced_nodes;

    root = rotateOdds(root, difference); // first pass
    for (int to_rotate = balanced_nodes / 2;
         to_rotate > 0;
         to_rotate /= 2)
        root = rotateOdds(root, to_rotate);
}

template <typename T>
inline BSTNode<T> *BST<T>::rotateOdds(Node *node, int to_rotate, int i, int n)
{
    if (n == to_rotate)
        return node;
    if (node == nullptr)
        return node;

    bool rotate = i % 2; // to rotate or not
    rotate && ++n;       // increase count if rotate

    node->right = rotateOdds(node->right, to_rotate, i + 1, n);

    if (rotate)
        return rotateLeft(node);
    return node;
}

template <typename T>
inline BSTNode<T> *BST<T>::rotateLeft(Node *node) const
{
    Node *right = node->right;
    node->right = right->left;
    right->left = node;
    return right;
}

template <typename T>
inline BSTNode<T> *BST<T>::rotateRight(Node *node) const
{
    Node *left = node->left;
    node->left = left->right;
    left->right = node;
    return left;
}

int main()
{
    // hard code value of nodes:
    int a[] = {69, 3, 66, 7, 2, 44, 98, 12, 13, 9, 100, 99, 200};
    const int n = sizeof(a) / sizeof(int);

    // insert nodes in tree:
    BST<int> tree;
    for (int i = 0; i < n; i++)
        tree.insert(a[i]);

    printTree(tree.getRoot()); // print tree
    puts("");                  //  new line

    tree.makeBackBone();       // transform to backbone
    printTree(tree.getRoot()); // print tree
    puts("");                  //  new line

    tree.balanceTree(n);       // balance using DSW
    printTree(tree.getRoot()); // print tree
    puts("");                  //  new line
    return 0;
}

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
