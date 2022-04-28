#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include "Record.hpp"
using namespace std;

// a general template class of a chained hashing table
template <typename type, const unsigned max_size>
class ChainedHash
{
public:
    using hashing_function = int (*)(const type &data);

private:
    list<Record<type>> table[max_size];   // array of lists of records
    int size = 0;                         // the number of records
    hashing_function hashingFn = nullptr; // the hashing function

public:
    ChainedHash(const hashing_function &hashingFn) : hashingFn(hashingFn) {}
    ~ChainedHash() { clear(); }

    // deletes all records
    // RECEIVES: nothing
    // RETURNS: nothing
    void clear()
    {
        size = 0;
        for (list<Record<type>> &ls : table)
            ls.clear();
    }

    // inserts a new element in table
    // RECEIVES: data = the contents of new record
    // RETURNS: index of new record in table
    int insert(const type &data)
    {
        int pos = hashingFn(data);
        table[pos].push_back(Record<type>(data));
        return pos;
    }

    list<Record<type>> &operator[](const int &pos)
    {
        if (pos < 0 || pos >= max_size)
            throw "Error: index is out of bounds of the table";
        return table[pos];
    }

    void display() const
    {
        for (int i = 0; i < max_size; i++)
        {
            printf("%2d) ", i);
            for (auto &record : table[i])
            {
                cout << record.get();
                printf(" --> ");
            }
            puts("-");
        }
        puts("");
    }

    // checks whether the table is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return size == 0; }

    // check whether the table is full or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool full() const { return size == max_size; }

    // returns the number of records in table
    // RECEIVES: nothing
    // RETURNS: the size
    unsigned length() const { return size; }

    // returns the starting element of table
    // RECEIVES: nothing
    // RETURNS: element at index 0
    list<Record<type>> &first() const { return table[0]; }

    // returns the last element of table
    // RECEIVES: nothing
    // RETURNS: element at size
    list<Record<type>> &last() const { return table[max_size - 1]; }
};

int hashFn(const int &data) { return data % 10; }

int main()
{
    ChainedHash<int, 10> h(hashFn);
    h.insert(1);
    h.insert(2);
    h.insert(5);
    h.insert(5);
    h.insert(6);
    h.insert(3);
    h.insert(4);
    h.insert(8);
    h.insert(12);
    h.insert(3);
    h.display();

    h[5].clear();
    h.display();

    return 0;
}