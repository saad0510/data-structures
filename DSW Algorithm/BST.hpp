#pragma once
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"

template <typename T>
class BST
{
public:
    BST();
    ~BST();

    using Node = BSTNode<T>;
    bool isEmpty() const;
    void insert(const T &data);
    void inorder(void (*visit)(Node *node));
    void preorder(void (*visit)(Node *node));
    void postorder(void (*visit)(Node *node));
    void breadthFirst(void (*visit)(Node *node));
    int height() const;
    void deleteNode(const T &data);
    Node *search(const T &data) const;
    Node *inorderSuccessor(const T &data) const;
    const Node *getRoot() const;
    void deleteTree(Node *node);

    // DSW functions:
    void makeBackBone();
    Node *makeBackBoneUtil(Node *node);
    int getBalanceNodes(const int total_nodes) const;
    void balanceTree(const int total_nodes);
    Node *rotateOdds(Node *node, int to_remove, int i = 1, int n = 0);

    Node *rotateLeft(Node *node) const;
    Node *rotateRight(Node *node) const;

private:
    Node *root;
    // --------- utility (helper) functions ----------
    bool insertUtil(const T &data, Node *node);
    void inorderUtil(void (*visit)(Node *node), Node *node);
    void preorderUtil(void (*visit)(Node *node), Node *node);
    void postorderUtil(void (*visit)(Node *node), Node *node);
    int heightUtil(Node *node) const;
    Node *deleteNodeUtil(const T &data, Node *node, Node *parent);
    Node *searchUtil(const T &data, Node *node) const;
};

#endif