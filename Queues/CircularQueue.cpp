#include <iostream>
using namespace std;

// a general template class of Queue implemented with circular arrays
template <typename type, const int max_size = 100>
class Queue
{
private:
public:
    int front;                // index of first element
    int rear;                 // index of last element
    type storage[max_size]{}; // the storage warehouse of elements
    unsigned size;            // the number of elements

    // returns the next index from given index in the circular array
    // RECEIVES: the index
    // RETURNS: the next index in array
    int inc(const int &it) const { return ((it + 1) % max_size); }

    // returns the previous index from given index in the circular array
    // RECEIVES: the index
    // RETURNS: the previous index in array
    int dec(const int &it) const { return ((it - 1) % max_size); }

public:
    // constructor:
    Queue() : front(0), rear(-1), size(0) {}

    // prints the contents of queue on console
    // note: '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        // logical illustration:
        if (empty()) // return if empty
            return;
        for (int i = front; i != rear; i = inc(i))
            cout << storage[i] << " ";
        cout << storage[rear] << " ";

        // physical illustration:
        // for (int i = 0; i < max_size; i++)
        // {
        //     if (i == front && i == rear)
        //         printf(" $");
        //     else if (i == front)
        //         printf(" +");
        //     else if (i == rear)
        //         printf(" -");
        //     else
        //         printf("  ");
        //     cout << storage[i] << " ";
        // }
        puts("");
    }

    // inserts a new element at the end of queue
    // RECEIVES: data = the contents of new element
    // RETURNS: the index of new element in queue
    int enqueue(const type &data)
    {
        if (full()) // error if already full
            throw "In enqueue() : queue is full";

        rear = inc(rear);
        storage[rear] = data;
        size++;
        return rear;
    }

    // removes an element from the front of queue
    // RECEIVES: nothing
    // RETURNS: the contents of removed element
    type dequeue()
    {
        if (empty()) // error if already empty
            throw "In dequeue() : queue is empty";

        type ret;
        ret = storage[front];
        storage[front] = 0;
        front = inc(front);
        size--;
        return ret;
    }

    // clears the queue completely
    // RECEIVES: nothing
    // RETURNS: nothing
    void clear()
    {
        front = 0;
        rear = -1;
        size = 0;
    }

    // returns whether the queue is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return size == 0; }

    // returns whether the queue is full or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool full() const { return size == max_size; }

    // returns the number of elements in queue
    // RECEIVES: nothing
    // RETURNS: numbre of elements
    unsigned length() const { return size; }

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
    q.display();
    for (int i = 1; i <= 5; i++)
    {
        q.enqueue(i);
        q.display();
    }
    for (int i = 1; i <= 4; i++)
    {
        q.dequeue();
        q.display();
    }
    for (int i = 1; i <= 9; i++)
    {
        q.enqueue(i);
        q.display();
    }
    for (int i = 1; i <= 10; i++)
    {
        q.dequeue();
        q.display();
    }
    q.enqueue(9);
    q.display();
    return 0;
}