#include <iostream>
using namespace std;

// a general template class of Queue implemented with arrays
template <typename type, const int max_size = 100>
class Queue
{
private:
    int front;              // index of first element
    int rear;               // index of last element
    type storage[max_size]; // the storage warehouse of elements

public:
    // constructor:
    Queue() : front(0), rear(-1) {}

    // prints the contents of queue on console
    // note: '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        for (int i = front; i <= rear; i++)
            cout << storage[i] << " ";
        puts("");
    }

    // inserts a new element at the end of queue
    // RECEIVES: data = the contents of new element
    // RETURNS: the index of new element in queue
    int enqueue(const type &data)
    {
        if (full()) // error if already full
            throw "In enqueue() : queue is full";
        rear++;
        storage[rear] = data;
        return rear;
    }

    // removes an element from the front of queue
    // RECEIVES: nothing
    // RETURNS: the contents of removed element
    type dequeue()
    {
        if (empty()) // error if already empty
            throw "In dequeue() : queue is empty";
        type ret = storage[front];
        // move all elements to left
        for (int i = front; i < rear; i++)
            storage[i] = storage[i + 1];
        rear--;
        return ret;
    }

    // returns whether the queue is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return rear == -1; }

    // returns whether the queue is full or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool full() const { return rear == max_size - 1; }

    // returns the number of elements in queue
    // RECEIVES: nothing
    // RETURNS: number of elements
    unsigned length() const { return rear + 1; }

    // returns the contents of element at front
    // RECEIVES: nothing
    // RETURNS: the element
    type begin() const { return storage[front]; }

    // returns the contents of element at rear
    // RECEIVES: nothing
    // RETURNS: the element
    type end() const { return storage[rear]; }
};

int main()
{
    Queue<int, 10> q;
    for (int i = 0; i < 10; i++)
    {
        q.enqueue(i + 1);
        q.display();
    }

    for (int i = 0; i < 10; i++)
    {
        q.dequeue();
        q.display();
    }
    return 0;
}