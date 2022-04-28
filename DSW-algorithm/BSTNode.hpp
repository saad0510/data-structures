#pragma once
#ifndef BSTNode_HPP
#define BSTNode_HPP

template <typename T>
class BSTNode
{
private:
public:
    T data;
    BSTNode<T> *right;
    BSTNode<T> *left;

    BSTNode() : BSTNode(0, nullptr, nullptr) {}
    BSTNode(const T &data) : BSTNode(data, nullptr, nullptr) {}
    BSTNode(const T &data, BSTNode<T> *left, BSTNode<T> *right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    bool isLeaf() const { return !right && !left; }
    bool hasOneChild() const { return (right && !left) || (!right && left); }
    bool hasTwoChild() const { return (right && left); }
};

#endif