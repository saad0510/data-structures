#include "BST.hpp"
#include <queue>
#include <iostream>

// constructor to create an empty tree
// arguments: nothing
template <typename T>
inline BST<T>::BST() { root = nullptr; }

// destructor to delete the entire tree
template <typename T>
inline BST<T>::~BST()
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
inline bool BST<T>::isEmpty() const { return !root; }

// a public function to insert a new node at its correct position in the tree
// arguments: 'data' = the data to insert (key of the node)
// returns: nothing
template <typename T>
inline void BST<T>::insert(const T &data)
{
    if (isEmpty()) // tree is empty?
    {              // insert directly:
        root = new Node(data);
        return;
    }
    insertUtil(data, root); // pass control to a helper function:
}

// a public & general purpose function to visit nodes in breadthFirst traversal order
// arguments: 'visit' = a function that receives every node.
// returns: nothing
template <typename T>
inline void BST<T>::breadthFirst(void (*visit)(Node *))
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
inline void BST<T>::inorder(void (*visit)(Node *node))
{
    inorderUtil(visit, root); // pass control to a helper function:
}

// a public & general purpose function to visit nodes in preorder traversal order
// arguments: 'visit' = a function that receives every node.
// returns: nothing
template <typename T>
inline void BST<T>::preorder(void (*visit)(Node *node))
{
    preorderUtil(visit, root); // pass control to a helper function:
}

// a public & general purpose function to visit nodes in postorder traversal order
// arguments: 'visit' = a function that receives every node.
// returns: nothing
template <typename T>
inline void BST<T>::postorder(void (*visit)(Node *node))
{
    postorderUtil(visit, root); // pass control to a helper function:
}

// a public function to delete the node of given key
// arguments: the key to delete
// returns: nothing
template <typename T>
inline void BST<T>::deleteNode(const T &data)
{
    if (isEmpty()) // tree is empty?
        return;    // there is nothing to delete

    if (root->isLeaf()) // if root is the only node
    {
        if (root->data == data) // if root is to be deleteds
        {                       // delete root:
            delete root;
            root = nullptr;
        }
        return;
    }
    root = deleteNodeUtil(data, root, nullptr); // pass control to a helper function:
}

// a public function to get height of the tree
// arguments: nothing
// returns: the calculated height
template <typename T>
inline int BST<T>::height() const
{
    return heightUtil(root); // pass control to a helper function:
}

// a public function that returns a non-modifiable handle to root
// arguments: nothing
// returns: the handle to root
template <typename T>
inline const BSTNode<T> *BST<T>::getRoot() const { return root; }

// a public function that returns a non-modifiable handle to the node of given key
// arguments: the given key to find
// returns: the handle to target
template <typename T>
inline BSTNode<T> *BST<T>::search(const T &data) const
{
    if (isEmpty())                 // tree is empty?
        return nullptr;            // nothing to search in
    return searchUtil(data, root); // pass control to a helper function:
}

// a public function that returns a non-modifiable handle to the inorder successor of the given node
// arguments: the given node
// returns: the handle to successor
template <typename T>
inline BSTNode<T> *BST<T>::inorderSuccessor(const T &data) const
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
inline void BST<T>::inorderUtil(void (*visit)(Node *node), Node *node)
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
inline void BST<T>::preorderUtil(void (*visit)(Node *node), Node *node)
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
inline void BST<T>::postorderUtil(void (*visit)(Node *node), Node *node)
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
inline int BST<T>::heightUtil(Node *node) const
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
bool BST<T>::insertUtil(const T &data, Node *node)
{
    if (node == nullptr)
        return true; // leaf node found

    if (data > node->data)
    {
        if (insertUtil(data, node->right)) // leaf node?
            node->right = new Node(data);  // insert
    }
    else
    {
        if (insertUtil(data, node->left)) // leaf node?
            node->left = new Node(data);  // insert
    }
    return false; // no leaf node exits
}

// a private function to delete the node of given key
// arguments: the key to delete
//            'node' = iterator
// returns: nothing
template <typename T>
inline BSTNode<T> *BST<T>::deleteNodeUtil(const T &data, Node *node, Node *parent)
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
    // if (node == nullptr)
    node->left = deleteNodeUtil(data, node->left, node);
    node->right = deleteNodeUtil(data, node->right, node);
    return ret;
}

// a private function that returns a non-modifiable handle to the node of given key
// arguments: the given key to find
//            'node' = iterating node
// returns: the handle to target
// travesal: 'preorder'
template <typename T>
inline BSTNode<T> *BST<T>::searchUtil(const T &data, Node *node) const
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
inline void BST<T>::deleteTree(Node *node)
{
    // pass the instructions to deletes
    inorder([](Node *node)
            { delete node; });
}
