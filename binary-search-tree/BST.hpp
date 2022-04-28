#pragma once
#ifndef BST_HPP
#define BST_HPP

#include "BSTNode.hpp"

template <typename T>
class BST
{
public:
    using Node = BSTNode<T>;
    using iterator = BSTNode<T> *;
    using const_iterator = const BSTNode<T> *;
    using callback = void (*)(Node *);

    BST();
    ~BST();

    bool isEmpty() const;
    void insert(const T &data);
    void inorder(const callback &visit);
    void preorder(const callback &visit);
    void postorder(const callback &visit);
    void breadthFirst(const callback &visit);
    int height() const;
    void deleteNode(const T &data);
    iterator search(const T &data) const;
    iterator inorderSuccessor(const T &data) const;
    const_iterator getRoot() const;
    void deleteTree(Node *node);

private:
    Node *root;
    // --------- utility (helper) functions ----------
    iterator insertUtil(const T &data, Node *node);
    void inorderUtil(const callback &visit, Node *node);
    void preorderUtil(const callback &visit, Node *node);
    void postorderUtil(const callback &visit, Node *node);
    int heightUtil(Node *node) const;
    Node *deleteNodeUtil(const T &data, Node *node);
    Node *searchUtil(const T &data, Node *node) const;
};

#endif