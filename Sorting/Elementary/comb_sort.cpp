#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

unsigned comb_sort(int arr[], int size)
{
    auto start = high_resolution_clock::now();
    int gap = size;
    while (true)
    {
        gap = (gap * 10) / 13;
        gap = gap < 1 ? 1 : gap;

        bool swapped = false;
        for (int i = 0; i < size - gap; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
        if (gap == 1 && swapped == false)
            break;
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
    int n = 10000;
    int arr[10000];
    for (short i = 0; i < n; i++)
        arr[i] = n - i;

    unsigned count = comb_sort(arr, n);

    printArr(arr, n);
    cout << "Sorted array in " << count << " microsec or " << count / 1000. << " milisec\n";

    return 0;
}
