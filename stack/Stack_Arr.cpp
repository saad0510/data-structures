#include <iostream>
using namespace std;

// a general template class of a Stack implemented using array
template <typename type, const unsigned max_size = 100>
class Stack
{
private:
    int top;                // index of element at top
    type storage[max_size]; // the storage warehouse of elements

public:
    // constructor:
    Stack() : top(-1) {}

    // prints the contents of stack on console
    // note: '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        for (int i = 0; i <= top; i++)
            cout << storage[i] << " ";
        puts("");
    }

    // inserts a new element at the top of stack
    // RECEIVES: data = the contents of new element
    // RETURNS: the index of new element in stack
    int push(const type &data)
    {
        if (full())
            throw "In push() : stack overflow";
        top++;
        storage[top] = data;
        return top;
    }

    // removes an element from the top of stack
    // RECEIVES: nothing
    // RETURNS: the contents of removed element
    type pop()
    {
        if (empty()) // error if already empty:
            throw "In pop() : stack underflow";
        type ret = storage[top];
        top--;
        return ret;
    }

    // returns whether the stack is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return top == -1; }

    // returns whether the stack is full or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool full() const { return top == max_size - 1; }

    // returns the number of elements in stack
    // RECEIVES: nothing
    // RETURNS: number of elements
    unsigned length() const { return top + 1; }

    // returns the contents of element at front
    // RECEIVES: nothing
    // RETURNS: the element
    type first() const { return storage[0]; }

    // returns the contents of element at top of stack
    // RECEIVES: nothing
    // RETURNS: the element at top
    type peek() const { return storage[top]; }
};

int main()
{
    Stack<int, 10> stack;
    for (int i = 0; i < 10; i++)
        stack.push(i);
    stack.display();

    for (int i = 0; i < 10; i++)
    {
        stack.pop();
        stack.display();
    }
    return 0;
}