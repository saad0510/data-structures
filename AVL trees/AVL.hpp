#pragma once
#ifndef AVL_HPP
#define AVL_HPP

#include "AVLNode.hpp"

template <typename T>
class AVL
{
public:
    AVL();
    ~AVL();

    using Node = AVLNode<T>;
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

private:
    Node *root;
    // --------- utility (helper) functions ----------
    Node *insertUtil(const T &data, Node *node);
    void inorderUtil(void (*visit)(Node *node), Node *node);
    void preorderUtil(void (*visit)(Node *node), Node *node);
    void postorderUtil(void (*visit)(Node *node), Node *node);
    int heightUtil(Node *node) const;
    Node *deleteNodeUtil(const T &data, Node *node);
    Node *searchUtil(const T &data, Node *node) const;
    // --------- rotation functions ----------
    Node *rotateLeft(Node *node);
    Node *rotateRight(Node *node);
};

#endif