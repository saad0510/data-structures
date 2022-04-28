#pragma once
#ifndef RECORD_HPP
#define RECORD_HPP

// a general template class for record units of any hash table
template <typename type>
class Record
{
private:
    type data;      // the contents of record
    bool available; // available or not

public:
    Record() : available(true) {}
    Record(const type &data) : data(data), available(false) {}

    // inserts new contents of record
    // RECEIVES: data = the contentt of new record
    // RETURNS: nothing
    void populate(const type &data)
    {
        if (available)
        {
            this->data = data;
            available = false;
        }
        else
            throw "Error: the record is already full";
    }

    // check whether the record is empty or not
    // RECEIVES: nothing
    // RETURNS: bool value
    bool empty() const { return available; }

    // clears the record for new data
    // RECEIVES: nothing
    // RETURNS: nothing
    void clear() { available = true; }

    // return the content of record
    // RECEIVES: nothing
    // RETURNS: the data
    type get() const { return data; }
};
#endif