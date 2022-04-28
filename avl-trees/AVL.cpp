#include "AVL.hpp"
#include <queue>
#include <iostream>

// utility function to get max value:
inline int max(const int &a, const int &b) { return a > b ? a : b; }

// constructor to create an empty tree
// arguments: nothing
template <typename T>
inline AVL<T>::AVL()
{
    root = nullptr;
}

// destructor to delete the entire tree
template <typename T>
inline AVL<T>::~AVL()
{
    if (!isEmpty()) // is tree not empty?
    {
        deleteTree(root); // call the delete function
        root = nullptr;
    }
}

// a public function to know if the tree is empty or not
// receives: nothing
// returns: a bool value
template <typename T>
inline bool AVL<T>::isEmpty() const { return root == nullptr; }

// a public function to insert a new node at its correct position in the tree
// arguments: 'data' = the data to insert (key of the node)
// returns: nothing
template <typename T>
inline void AVL<T>::insert(const T &data)
{
    root = insertUtil(data, root); // pass control to a helper function:
}

// a public & general purpose function to visit nodes in breadthFirst traversal order
// arguments: 'visit' = a function that receives every node.
// returns: nothing
template <typename T>
inline void AVL<T>::breadthFirst(void (*visit)(Node *))
{
    if (isEmpty()) // is tree empty?
        return;

    std::queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *n = q.front();
        q.pop();
        visit(n);
        if (n->left != nullptr)
            q.push(n->left);
        if (n->right != nullptr)
            q.push(n->right);
    }
}

// a public & general purpose function to visit nodes in inorder traversal order
// arguments: 'visit' = a function that receives every node.
// returns: nothing
template <typename T>
inline void AVL<T>::inorder(void (*visit)(Node *node))
{
    inorderUtil(visit, root); // pass control to a helper function:
}

// a public & general purpose function to visit nodes in preorder traversal order
// arguments: 'visit' = a function that receives every node.
// returns: nothing
template <typename T>
inline void AVL<T>::preorder(void (*visit)(Node *node))
{
    preorderUtil(visit, root); // pass control to a helper function:
}

// a public & general purpose function to visit nodes in postorder traversal order
// arguments: 'visit' = a function that receives every node.
// returns: nothing
template <typename T>
inline void AVL<T>::postorder(void (*visit)(Node *node))
{
    postorderUtil(visit, root); // pass control to a helper function:
}

// a public function to delete the node of given key
// arguments: the key to delete
// returns: nothing
template <typename T>
inline void AVL<T>::deleteNode(const T &data)
{
    root = deleteNodeUtil(data, root); // pass control to a helper function:
}

// a public function to get height of the tree
// arguments: nothing
// returns: the calculated height
template <typename T>
inline int AVL<T>::height() const
{
    return heightUtil(root); // pass control to a helper function:
}

// a public function that returns a non-modifiable handle to root
// arguments: nothing
// returns: the handle to root
template <typename T>
inline const AVLNode<T> *AVL<T>::getRoot() const { return root; }

// a public function that returns a non-modifiable handle to the node of given key
// arguments: the given key to find
// returns: the handle to target
template <typename T>
inline AVLNode<T> *AVL<T>::search(const T &data) const
{
    return searchUtil(data, root); // pass control to a helper function:
}

// a public function that returns a non-modifiable handle to the inorder successor of the given node
// arguments: the given node
// returns: the handle to successor
template <typename T>
inline AVLNode<T> *AVL<T>::inorderSuccessor(const T &data) const
{
    Node *node = search(data); /// get the handle to node with given key

    if (node->right == nullptr) // right child is empty?
        return nullptr;         // inorder successor is the parent

    node = node->right;           // move right
    while (node->left != nullptr) // stop before an end
        node = node->left;        // keep moving left
    return node;
}

// ---------------------- private and helper functions -------------------------------

// a private and helper function to continue inorder traversal
// arguments: 'visit' = a function that receives every node.
//            'node' = a node to keep track of iteration
// returns: nothing
template <typename T>
inline void AVL<T>::inorderUtil(void (*visit)(Node *node), Node *node)
{
    if (node != nullptr) // base case
    {
        inorderUtil(visit, node->left);
        visit(node);
        inorderUtil(visit, node->right);
    }
}

// a private and helper function to continue preorder traversal
// arguments: 'visit' = a function that receives every node.
//            'node' = a node to keep track of iteration
// returns: nothing
template <typename T>
inline void AVL<T>::preorderUtil(void (*visit)(Node *node), Node *node)
{
    if (node != nullptr) // base case
    {
        visit(node);
        preorderUtil(visit, node->left);
        preorderUtil(visit, node->right);
    }
}

// a private and helper function to continue postorder traversal
// arguments: 'visit' = a function that receives every node.
//            'node' = a node to keep track of iteration
// returns: nothing
template <typename T>
inline void AVL<T>::postorderUtil(void (*visit)(Node *node), Node *node)
{
    if (node != nullptr) // base case
    {
        postorderUtil(visit, node->left);
        postorderUtil(visit, node->right);
        visit(node);
    }
}

// a private function to get height of given node
// arguments: 'node' = the node to calculate height
// returns: the calcualted height
template <typename T>
inline int AVL<T>::heightUtil(Node *node) const
{
    if (node == nullptr)
        return -1;

    int LeftH = heightUtil(node->left);
    int RightH = heightUtil(node->right);
    return (LeftH > RightH) ? (LeftH + 1) : (RightH + 1); // max(leftH, rightH) + 1
}

// a private function to insert a new node at its correct position
// arguments: 'data' = the data to insert (key of the node)
//            'node' = the node to insert from
// returns: nothing
template <typename T>
inline AVLNode<T> *AVL<T>::insertUtil(const T &data, Node *node)
{
    if (node == nullptr)
        return new Node(data);

    if (data > node->data)
        node->right = insertUtil(data, node->right);
    else if (data < node->data)
        node->left = insertUtil(data, node->left);
    else
        return node;

    node->update();
    const int BF = node->balanceFactor;

    if (BF != -1 && BF != 0 && BF != 1)
    {
        if (BF > 1 && data > node->right->data) // LL rotation
            return rotateLeft(node);
        if (BF > 1 && data < node->right->data) // RL rotation
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (BF < -1 && data < node->left->data) // RR rotation
        {
            return rotateRight(node);
        }
        if (BF < -1 && data > node->left->data) // LR rotation
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        };
    }
    return node;
}

// a private function to delete the node of given key
// arguments: the key to delete
//            'node' = iterator
// returns: nothing
template <typename T>
inline AVLNode<T> *AVL<T>::deleteNodeUtil(const T &data, Node *node)
{
    if (node == nullptr)
        return nullptr;

    // deletion logic:
    Node *ret = node;
    if (node->data == data)
    {
        if (node->isLeaf())
        {
            delete node;
            ret = nullptr;
        }
        else if (node->hasOneChild())
        {
            if (node->left)
                ret = node->left;
            else
                ret = node->right;
            delete node;
        }
        else if (node->hasTwoChild())
        {
            Node *succ = inorderSuccessor(data);
            node->data = succ->data;
            succ->data = data;
            deleteNodeUtil(data, root, node);
        }
        return ret;
    }
    // if the current node is not matched with the key:
    node->left = deleteNodeUtil(data, node->left);   // find in left sub tree
    node->right = deleteNodeUtil(data, node->right); // find in right sub tree

    node->update();          // update the height of tree (if changed)
    const int BF = node->BF; // get the balance factor of node

    if (BF != -1 && BF != 0 && BF != 1) // is the node balanced?
    {                                   // rotate accordingly:
        if (BF > 1)
            return leftRotate(node);
        else if (BF < -1)
            return rightRotate(node);
    }
    return node; // no change in the tree
}

// a private function that returns a non-modifiable handle to the node of given key
// arguments: the given key to find
//            'node' = iterating node
// returns: the handle to target
// travesal: 'preorder'
template <typename T>
inline AVLNode<T> *AVL<T>::searchUtil(const T &data, Node *node) const
{
    if (node == nullptr)    // no node?
        return nullptr;     // no handle
    if (node->data == data) // is the key located?
        return node;        // return handle

    Node *target = searchUtil(data, node->left); // search handle from left-subtree
    if (target == nullptr)                       // key was not found in left-subtree?
        target = searchUtil(data, node->right);  // search handle from right-subtree
    return target;                               // return handle
}

// a private function to delete the tree from memory
// arguments: 'node' = the node to start deleting from
// returns: nothing
// notes: all nodes are deleted in inorder traversal
template <typename T>
inline void AVL<T>::deleteTree(Node *node)
{
    // pass the instructions to deletes
    inorder([](Node *node)
            { delete node; });
}

// a private function to rotate left a given node
// arguments: 'node' = the node to rotate
// returns: the reference of final transformation
template <typename T>
inline AVLNode<T> *AVL<T>::rotateLeft(Node *node)
{
    Node *right = node->right;

    node->right = right->left;
    right->left = node;

    node->update();
    right->update();
    return right;
}

// a private function to rotate right a given node
// arguments: 'node' = the node to rotate
// returns: the reference of final transformation
template <typename T>
inline AVLNode<T> *AVL<T>::rotateRight(Node *node)
{
    Node *left = node->left;

    node->left = left->right;
    left->right = node;

    node->update();
    left->update();
    return left;
}