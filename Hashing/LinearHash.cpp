#include <iostream>
#include <string>
#include <cstring>
#include "Record.hpp"
using namespace std;

// a general template class of a linear hashing table
template <typename type, const unsigned max_size>
class LinearHash
{
public:
    using hashing_function = int (*)(const type &data);

private:
    Record<type> table[max_size];         // array of records
    int size;                             // the number of records
    hashing_function hashingFn = nullptr; // the hashing function

public:
    // constructors & deconstructors:
    LinearHash(const hashing_function &hashingFn) : size(0), hashingFn(hashingFn) {}
    ~LinearHash() {}

    // prints all records on the console
    // note: '<<' operator is used
    // RECEIVES: nothing
    // RETURNS: nothing
    void display() const
    {
        for (int i = 0; i < max_size; i++)
        {
            printf("%2d) - ", i);
            if (!table[i].empty())
                cout << table[i].get();
            puts("");
        }
        puts("");
    }

    // deletes all records
    // RECEIVES: nothing
    // RETURNS: nothing
    void clear()
    {
        size = 0;
        for (Record<type> &record : table)
            record.clear();
    }

    // inserts a new element in table
    // RECEIVES: data = the contents of new record
    // RETURNS: index of new record in table
    int insert(const type &data)
    {
        if (full()) // error if already full
            throw "Error: table overflow";

        int pos = hashingFn(data); // get position of element
        if (table[pos].empty())    // insert directly if empty
            table[pos].populate(data);
        else
        { // find the position in table and insert
            do
            {
                pos = (pos + 1) % max_size;
            } while (!table[pos].empty());
            table[pos].populate(data);
        }
        size++;
        return pos;
    }

    // deletes a record from given position the table
    // RECEIVES: the index to remove
    // RETURNS: the contents of deleted record
    Record<type> remove(const int &pos)
    {
        if (pos < 0 || pos >= max_size) // error if index is invalid
            throw "Error: index is out of bounds of the table";
        if (empty()) // errot if already empty()
            throw "Error: rable underflow";

        Record<type> ret = table[pos];
        table[pos].clear();
        return ret;
    }

    Record<type> &operator[](const int &pos)
    {
        if (pos < 0 || pos >= max_size)
            throw "Error: index is out of bounds of the table";
        return table[pos];
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
    Record<type> &first() const { return table[0]; }

    // returns the last element of table
    // RECEIVES: nothing
    // RETURNS: element at size
    Record<type> &last() const { return table[size - 1]; }
};

int hashFn(const int &data) { return data % 10; }

int main()
{
    LinearHash<int, 10> h(hashFn);
    h.insert(1);
    h.insert(2);
    h.insert(5);
    h.insert(5);
    h.display();

    return 0;
}