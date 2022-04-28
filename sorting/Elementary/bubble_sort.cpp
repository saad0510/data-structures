#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

unsigned bubble_sort(int arr[], int size)
{
    auto start = high_resolution_clock::now();
    bool again = true;
    for (short pass = 0; pass <= size - 2 && again; pass++)
    {
        bool changed = false;
        for (short i = 0, again = false; i <= size - 2 - pass; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                again = true;
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

void printArr(int arr[], int size)
{
    for (short i = 0; i < size; i++)
        printf("%d ", arr[i]);
    puts("");
}

int main()
{
    int n = 10;
    int arr[10];
    for (short i = 0; i < n; i++)
        arr[i] = n - i;

    unsigned count = bubble_sort(arr, n);
    printArr(arr, n);
    cout << "Sorted array in " << count << " microsec or " << count / 1000. << " milisec\n";

    return 0;
}
