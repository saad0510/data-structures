#ifndef P_QUEUE
#define P_QUEUE

#include <iostream>
using namespace std;

// a general template structure for node of a priority queue
template <typename type>
struct Node
{
    type data;
    int priority;
    Node<type> *next;
    // constructor:
    Node(int data, int priority)
    {
        this->data = data;
        this->priority = priority;
        this->next = nullptr;
    }
};

// a general template class for node of a priority queue
template <typename type>
class PriorityQueue
{
private:
    Node<type> *front;
    Node<type> *rear;
    unsigned size = 0;

public:
    // type aliases:
    using iterator = Node<type> *;
    using const_iterator = const Node<type> *;

    // constructors & destructors:
    PriorityQueue() : front(0), rear(0) {}
    ~PriorityQueue() { clear(); }

    // returns whether queue is empty or not
    // RECEIVES: nothing
    // RETURNS: nothing
    bool empty() const
    {
        return front == nullptr;
    }

    // returns the number of elements in queue
    // RECEIVES: nothing
    // RETURNS: unsigned value
    unsigned length() const
    {
        return size;
    }

    // returns an iterator to the node at front
    // RECEIVES: nothing
    // RETURNS: type data
    iterator begin() const
    {
        if (empty())
            return 0;
        return front;
    }

    // returns an iterator to the node at rear
    // RECEIVES: nothing
    // RETURNS: type data
    iterator end() const
    {
        if (empty())
            return 0;
        return rear;
    }

    // prints all elements in "priority(data)" format:
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        iterator temp = front;
        while (temp != nullptr)
        {
            cout << temp->priority << "(" << temp->data << ") ";
            temp = temp->next;
        }
        puts("");
    }

    // inserts a new node w.r.t highest priority
    // RECEIVES: data = the contents of node
    //           priority = the priority of data
    // RETURNS: the logical index of new node in the queue
    int enque(int data, int priority)
    {
        if (empty())
        {
            front = rear = new Node<type>(data, priority);
            size++;
            return 0;
        }

        iterator temp = front;
        iterator prev = nullptr;
        bool inserted = false;

        while (temp != nullptr)
        {
            if (priority > temp->priority) // given priority is greater than the temp.priority?
            {
                if (prev == nullptr) // is it the first node?
                {                    // insert at front:
                    Node<type> *newNode = new Node<type>(data, priority);
                    newNode->next = front;
                    front = newNode;
                }
                else
                { // insert before temp:
                    Node<type> *newNode = new Node<type>(data, priority);
                    newNode->next = temp;
                    prev->next = newNode;
                }
                // mark as inserted:
                inserted = true;
                break;
            }
            // move ahead:
            prev = temp;
            temp = temp->next;
        }
        if (inserted == false) // priorty is lowest of all?
        {                      // insert at end:
            rear->next = new Node<type>(data, priority);
            rear = rear->next;
        }
        return size++;
    }

    // will remove elements from front
    // RECEIVES: nothing
    // RETURNS: the contents of removed node
    type deque()
    {
        if (empty())
            throw "Exception: In deque() = the queue is already empty";

        Node<type> *to_rem = front; // to remove
        type to_ret = front->data;  // to return
        front = front->next;        // move front ahead
        delete to_rem;
        size--;
        return to_ret;
    }

    // deletes all elements of queue
    // RECEIVES: nothing
    // RETURNS: nothing
    void clear()
    {
        while (front != nullptr)
        {
            Node<type> *to_rem = front; // to remove
            front = front->next;
            delete to_rem;
        }
        front = rear = nullptr; // marks as empty
        size = 0;
    }
};

#endif