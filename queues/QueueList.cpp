#include <iostream>
using namespace std;

// a general template structure for node of a Queue
template <typename type>
struct Node
{
    type data;  // the contents of node
    Node *next; // points to next node in queue
    // constructor:
    Node(const type &data, Node *next)
        : data(data), next(next) {}
};

// a general template class of a variable length Queue
template <typename type>
class Queue
{
private:
    Node<type> *front; // points to first node
    Node<type> *rear;  // points to last node
    unsigned size;     // the number of nodes

public:
    // type aliases for readability:
    using iterator = Node<type> *;
    using const_iterator = const Node<type> *;

    // constructors & deconstructors:
    Queue() : front(nullptr), rear(nullptr), size(0){};
    ~Queue() { clear(); }

    // prints the elements of queue on console
    // note: the '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        iterator it = front;
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
            Node<type> *remove = front;
            front = front->next;
            delete remove;
        }
        // revert the empty condition of queue:
        size = 0;
        front = rear = nullptr;
    }

    // inserts a new element at the end of queue
    // RECEIVES: data = the contents of new node
    // RETURNS: the logical index of new node in queue (starting from 0)
    int enqueue(const type &data)
    {
        if (empty())
        {
            front = rear = new Node<type>(data, nullptr);
        }
        else
        {
            rear->next = new Node<type>(data, nullptr);
            rear = rear->next;
        }
        return size++;
    }

    // deletes a node from the front of list
    // RECEIVES: nothing
    // RETURNS: the contents of deleted node
    type dequeue()
    {
        if (empty()) // error if empty:
            throw "In dequeue() : queue is alread empty";
        size--;

        type ret;          // will hold the contents of deleted node
        if (front == rear) // there is only one node?
        {                  // yes: delete directly:
            ret = front->data;
            delete front;
            front = rear = nullptr; // no node in list
        }
        else
        { // delete head:
            Node<type> *remove = front;
            ret = front->data;
            front = front->next;
            delete remove;
        }
        return ret;
    }

    // check whether the queue is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return front == nullptr; }

    // returns the number of nodes in queue
    // RECEIVES: nothing
    // RETURNS: the size
    unsigned length() const { return size; }

    // returns an iterator to the start of queue
    // RECEIVES: nothing
    // RETURNS: head
    iterator begin() const { return front; }

    // returns an iterator to the end of queue
    // RECEIVES: nothing
    // RETURNS: end point (nullptr)
    iterator end() const { return nullptr; }
};

int main()
{
    Queue<int> queue;
    for (short unsigned i = 1; i <= 5; i++)
    {
        queue.enqueue(i);
        queue.display();
    }

    for (short unsigned i = 1; i <= 5; i++)
    {
        queue.dequeue();
        queue.display();
    }

    return 0;
}