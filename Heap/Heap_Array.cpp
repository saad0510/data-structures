#include <iostream>
using namespace std;

template <typename T, const int capacity = 100>
class Heap
{
private:
    T pool[capacity];
    int size;

    void heapifyUtil(int index, int limit)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < limit && pool[left] < pool[largest])
            largest = left;
        if (right < limit && pool[right] < pool[largest])
            largest = right;

        if (largest != index)
        {
            swap(pool[largest], pool[index]);
            heapifyUtil(largest, limit);
        }
    }

public:
    Heap() { size = 0; }
    ~Heap() {}

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }

    int insert(const T &data)
    {
        if (isFull())
        {
            puts("Heap overflow");
            return -1;
        }

        pool[size] = data;
        size++;
        heapify();

        return size;
    }

    T remove(const T &data)
    {
        if (isEmpty())
        {
            puts("Heap underflow");
            return 0;
        }

        int i;
        for (i = 0; i < size; i++)
            if (pool[i] == data)
                break;

        swap(pool[i], pool[size - 1]);
        --size;
        heapify();

        return pool[i];
    }

    void display() const
    {
        for (int i = 0; i < size; i++)
            cout << pool[i] << " ";
        puts("");
    }

    void heapify()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapifyUtil(i, size);
    }

    void heapSort()
    {
        for (int i = size - 1, j = 0; i >= 0; i--, j++)
        {
            swap(pool[0], pool[size - 1 - j]);
            heapifyUtil(0, size - 1 - j);
        }
    }
};

int main()
{
    Heap<int, 10> h;
    h.insert(8);
    h.insert(6);
    h.insert(9);
    h.insert(2);
    h.insert(20);
    h.insert(3);
    h.insert(1);
    h.display();

    h.heapSort();
    h.display();
    return 0;
}