#include <iostream>

// a general template structure for node of a singly linked list
template <typename type>
struct Node
{
    type data;  // the contents of node
    Node *next; // points to next node in list
    // constructor:
    Node(const type &data, Node *next)
        : data(data), next(next) {}
};

// a general template class of a singly linked list
template <typename type>
class SLL
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
    SLL() : head(nullptr), tail(nullptr), size(0){};
    ~SLL() { clear(); }

    // prints the elements of list on console
    // note: the '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        iterator it = head;
        while (it != nullptr)
        {
            std::cout << it->data << " ";
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
            Node<type> *remove = head;
            head = head->next;
            delete remove;
        }
        // revert the empty condition of list:
        size = 0;
        head = tail = nullptr;
    }

    // inserts a new element at the end of list
    // RECEIVES: data = the contents of new node
    // RETURNS: the logical index of new node in list (starting from 0)
    int push_back(const type &data)
    {
        if (empty())
        { // insert directly:
            head = tail = new Node<type>(data, nullptr);
        }
        else
        { // insert at tail:
            tail->next = new Node<type>(data, nullptr);
            tail = tail->next;
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
            head = tail = new Node<type>(data, nullptr);
        }
        else
        { // insert at head:
            Node<type> *newnode = new Node<type>(data, head);
            head = newnode;
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
        {                 // yes: delete directly:
            ret = head->data;
            delete head;
            head = tail = nullptr; // no node in list
        }
        else
        { // get 2nd-last node:
            iterator secondLast = head;
            while (secondLast->next != tail)
                secondLast = secondLast->next;
            // delete last:
            Node<type> *to_remove = tail;
            ret = tail->data;
            tail = secondLast;
            tail->next = nullptr;
            delete to_remove;
        }
        size--;
        return ret;
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
            Node<type> *to_remove = head;
            ret = head->data;
            head = head->next;
            delete to_remove;
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

        iterator it = head, // points to current node of iteration
            prev = nullptr; // points to previous node of 'it'

        while (it != nullptr) // move till end of list
        {
            if (it->data == data) // data is found?
            {
                if (prev == nullptr) // is it the first node?
                {                    // delete only head:
                    Node<type> *remove = head;
                    head = head->next;
                    delete remove;
                    // update iterators:
                    prev = nullptr;
                    it = head;
                }
                else if (it == tail) // is it the last node?
                {                    // delete only last:
                    tail = prev;
                    tail->next = nullptr;
                    delete it;
                    // update iterators:
                    prev = tail;
                    it = nullptr;
                }
                else
                { // delete current node & adjust links
                    prev->next = it->next;
                    Node<type> *to_remove = it;
                    it = it->next;
                    delete to_remove;
                }
                size--;
                continue; // because iterators are already updated
            }
            // update iterators:
            prev = it;
            it = it->next;
        }
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
    SLL<int> list;
    for (short unsigned i = 0; i < 5; i++)
    {
        list.push_front(i);
    }
    list.push_front(1);
    list.push_back(1);
    list.display();
    list.remove(1);
    list.display();

    for (short unsigned i = 0; i < 4; i++)
    {
        list.pop_front();
        list.display();
    }

    return 0;
}