#include <iostream>
using namespace std;

// a general template structure for node of a Stack
template <typename type>
struct Node
{
    type data;  // the contents of node
    Node *next; // points to next node in Stack
    // constructor:
    Node(const type &data, Node *next)
        : data(data), next(next) {}
};

// a general template class of a variable length Stack
template <typename type>
class Stack
{
private:
    Node<type> *top; // points to top node
    unsigned size;   // the number of nodes

public:
    // type aliases for readability:
    using iterator = Node<type> *;
    using const_iterator = const Node<type> *;

    // constructors & deconstructors:
    Stack() : top(nullptr), size(0) {}
    ~Stack() { clear(); }

    // prints the elements of stack on console
    // note: the '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        iterator it = top;
        while (it != nullptr)
        {
            cout << it->data << " ";
            it = it->next;
        }
        puts("");
    }

    // deletes all nodes from heap memory
    // RECEIVES: nothing
    // RETURNS: nothing
    void clear()
    {
        while (!empty())
        {
            Node<type> *remove = top;
            top = top->next;
            delete remove;
        }
        // revert the empty condition of queue:
        size = 0;
        top = nullptr;
    }

    // inserts a new element at the top of stack
    // RECEIVES: data = the contents of new node
    // RETURNS: the logical index of new node in stack (starting from 0)
    int push(const type &data)
    {
        top = new Node<type>(data, top);
        if (top == nullptr) // if heap is full
            throw "In push() : stack overflow (no memory available)";
        return size++;
    }

    // deletes a node from the top of queue
    // RECEIVES: nothing
    // RETURNS: the contents of deleted node
    type pop()
    {
        if (empty()) // if already empty
            throw "In pop() : stack underflow";

        Node<type> *remove = top;
        type ret = top->data;
        top = top->next;
        size--;
        delete remove;
        return ret;
    }

    // check whether the stack is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return top == nullptr; }

    // returns the number of nodes in stack
    // RECEIVES: nothing
    // RETURNS: the size
    unsigned length() const { return size; }

    // returns an iterator to the top of stack
    // RECEIVES: nothing
    // RETURNS: top
    iterator peek() const { return top; }

    // returns an iterator to the end of stack
    // RECEIVES: nothing
    // RETURNS: end point (nullptr)
    iterator end() const { return nullptr; }
};

int main()
{
    Stack<int> stack;
    for (int i = 0; i < 10; i++)
        stack.push(i + 1);
    stack.display();

    for (int i = 0; i < 10; i++)
    {
        stack.pop();
        stack.display();
    }
    return 0;
}