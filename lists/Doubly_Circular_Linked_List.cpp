#include <iostream>
using namespace std;

// a general template structure for node of a doubly linked list
template <typename type>
struct Node
{
    type data;  // the contents of node
    Node *next; // points to next node in list
    Node *prev; // points to previous node in list
    // constructor:
    Node(const type &data, Node *prev, Node *next)
        : data(data), prev(prev), next(next) {}
};
// a general template class of a doubly linked list
template <typename type>
class DCLL
{
private:
    Node<type> *head; // points to first node
    Node<type> *tail; // points to last node
    unsigned size;    // the number of nodes

public:
    // type aliases for readability:
    using iterator = Node<type> *;
    using const_iterator = const Node<type> *;

    // constructors & deconstructors:
    DCLL() : head(nullptr), tail(nullptr), size(0){};
    ~DCLL() { clear(); }

    // prints the elements of list on console
    // note: the '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        iterator temp = head;
        while (temp != tail)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << temp->data << " ";
        puts("");
    }

    // deletes all nodes from heap memory
    // RECEIVES: nothing
    // RETURNS: nothing
    void clear()
    {
        if (empty()) // return if empty
            return;

        while (head != tail)
        {
            Node<type> *remove = head;
            head = head->next;
            delete remove;
        }
        delete head;
        // revert the empty condition of list:
        head = tail = nullptr;
        size = 0;
    }

    // inserts a new element at the end of list
    // RECEIVES: data = the contents of new node
    // RETURNS: the logical index of new node in list (starting from 0)
    int push_back(const type &data)
    {
        if (empty())
        { // insert directly:
            head = tail = new Node<type>(data, nullptr, nullptr);
            head->prev = tail;
            tail->next = head;
        }
        else
        { // insert at tail:
            tail->next = new Node<type>(data, tail, head);
            tail = tail->next;
            head->prev = tail;
        }
        return size++;
    }

    // inserts a new element at the front of list (index = 0)
    // RECEIVES: data = the contents of new node
    // RETURNS: nothing
    void push_front(const type &data)
    {
        if (empty())
        { // insert directly:
            head = tail = new Node<type>(data, nullptr, nullptr);
            head->prev = tail;
            tail->next = head;
        }
        else
        { // insert at head:
            Node<type> *newnode = new Node<type>(data, tail, head);
            head->prev = newnode;
            head = newnode;
            tail->next = head;
        }
        size++;
    }

    // deletes a node at from the end of list
    // RECEIVES: nothing
    // RETURNS: the contents of deleted node
    type pop_back()
    {
        if (empty()) // error if empty:
            throw "In pop_back() : list is already empty";

        type ret;         // will hold the contents of deleted node
        if (head == tail) // there is only one node?
        {                 // yes : delete directly :
            ret = head->data;
            delete head;
            head = tail = nullptr; // no node in list
        }
        else
        { // get 2nd-last node:
            Node<type> *secondLast = tail->prev;
            // delete tail:
            Node<type> *remove = tail;
            ret = tail->data;
            tail = secondLast;
            tail->next = head;
            head->prev = tail;
            delete remove;
        }
        size--;
        return ret;
    }

    // deletes all occurrences of given data from the list
    // RECEIVES: data = the content to delete
    // RETURNS: nothing
    void remove(const type &data)
    {
        if (empty()) // error if empty:
            throw "In pop_back() : list is already empty";

        iterator it = head; // points to current node of iteration
        while (true)        // move till end of list
        {
            if (it->data == data) // data is found?
            {
                if (it == head) // is it the first node?
                {               // delete only head:
                    Node<type> *remove = head;
                    head = head->next;
                    head->prev = tail;
                    tail->next = head;
                    delete remove;
                    it = head; // update iterator
                }
                else if (it == tail) // is it the last node?
                {                    // delete only last:
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                    delete it;
                    it = tail; // update iterator
                }
                else
                { // delete current node & adjust links
                    Node<type> *prev = it->prev;
                    prev->next = it->next;
                    it->next->prev = prev;
                    Node<type> *to_remove = it;
                    it = it->next; // update iterator
                    delete to_remove;
                }
                size--;
                continue; // because iterators are already updated
            }
            it = it->next; // update iterator
            if (it == head)
                break;
        }
    }

    // deletes a node from the front of list
    // RECEIVES: nothing
    // RETURNS: the contents of deleted node
    type pop_front()
    {
        if (empty()) // error if empty:
            throw "In pop_front() : list is alread empty";

        type ret;         // will hold the contents of deleted node
        if (head == tail) // there is only one node?
        {                 // yes: delete directly:
            ret = head->data;
            delete head;
            head = tail = nullptr; // no node in list
        }
        else
        { // delete head:
            Node<type> *remove = head;
            ret = head->data;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete remove;
        }
        size--;
        return ret;
    }

    // check whether the list is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return head == nullptr; }

    // returns the number of nodes in list
    // RECEIVES: nothing
    // RETURNS: the size
    unsigned length() const { return size; }

    // returns an iterator to the start of list
    // RECEIVES: nothing
    // RETURNS: head
    iterator begin() const { return head; }

    // returns an iterator to the end of list
    // RECEIVES: nothing
    // RETURNS: end point (nullptr)
    iterator end() const { return nullptr; }
};

int main()
{
    DCLL<int> list;
    for (short unsigned i = 0; i < 5; i++)
    {
        list.push_back(i);
    }
    list.display();
    list.push_back(1);
    list.push_front(1);
    list.display();
    list.remove(1);
    list.display();

    for (short unsigned i = 0; i < 4; i++)
    {
        list.pop_back();
        list.display();
    }

    return 0;
}