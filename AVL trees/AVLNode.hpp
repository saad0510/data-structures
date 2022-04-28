#pragma once
#ifndef AVLNode_HPP
#define AVLNode_HPP

template <typename T>
class AVLNode
{
private:
public:
    T data;
    int height;
    int balanceFactor;
    AVLNode<T> *right;
    AVLNode<T> *left;

    AVLNode() : AVLNode(0, nullptr, nullptr) {}
    AVLNode(const T &data) : AVLNode(data, nullptr, nullptr) {}
    AVLNode(const T &data, AVLNode<T> *left, AVLNode<T> *right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        this->height = 0;
        this->balanceFactor = 0;
    }

    bool isLeaf() const
    {
        return !right && !left;
    }
    bool hasOneChild() const
    {
        return (right && !left) || (!right && left);
    }
    bool hasTwoChild() const
    {
        return (right && left);
    }

    void update()
    {
        int leftH = getHeight(left);
        int rightH = getHeight(right);
        height = 1 + (leftH > rightH ? leftH : rightH);
        balanceFactor = rightH - leftH;
    }

    static int getHeight(const AVLNode<T> *node) { return node ? node->height : -1; }
};

#endif