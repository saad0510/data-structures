#ifndef DSA_H
#define DSA_H
#pragma once

template <typename type>
class DSA
{
private:
	type *ptr;
	unsigned capacity, length;

	type *allocate(const unsigned capacity) const
	{
		type *tempPtr = new type[capacity];
		return tempPtr;
	}

public:
	DSA(const unsigned n)
	{
		ptr = allocate(n);
		capacity = n;
		length = 0;
	}
	~DSA()
	{
		clear();
	}

	void push_back(const type data)
	{
		if (length == capacity)
			resize(capacity * capacity);
		ptr[length++] = data;
	}

	void resize(const unsigned newSize)
	{
		type *tmp = allocate(newSize);
		const unsigned newLength = length;
		// copy prev data:
		for (unsigned i = 0; i < length && i < newSize; i++)
			tmp[i] = ptr[i];
		clear();

		ptr = tmp;
		length = newLength;
		capacity = newSize;
	}

	void shrink()
	{
		type *shrinkedPtr = allocate(length);
		// copying prev data
		for (unsigned i = 0; i < length; i++)
			shrinkedPtr[i] = ptr[i];
		const unsigned newLength = length;
		clear();

		ptr = shrinkedPtr;
		length = newLength;
		capacity = newLength;
	}

	void clear()
	{
		if (ptr == nullptr)
			return;

		delete[] ptr;
		capacity = 0;
		length = 0;
		ptr = nullptr;
	}

	type &operator[](const int index) const
	{
		// todo
		if (index < 0 || index >= length)
			throw "In operator[] : index is out of bounds";
		return ptr[index];
	}

	unsigned getLength() const
	{
		return length;
	}
	unsigned getCapacity() const
	{
		return capacity;
	}
};
#endif