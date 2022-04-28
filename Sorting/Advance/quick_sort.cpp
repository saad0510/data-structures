#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

void printArr(int arr[], int start, int end)
{
    for (short i = start; i <= end; i++)
        printf("%d ", arr[i]);
    puts("");
}

// first element as pivot
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int pivotIndex = high;

    int i = low;
    for (unsigned j = low; j <= high - 1; j++)
        if (arr[j] < pivot)
        {
            if (i != j)
                swap(arr[i], arr[j]);
            i++;
        }
    swap(arr[i], arr[pivotIndex]);
    return i;
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        quick_sort(arr, low, pivotIndex - 1);
        quick_sort(arr, pivotIndex + 1, high);
    }
}

unsigned quick_sort_start(int arr[], int low, int high)
{
    auto start = high_resolution_clock::now();

    quick_sort(arr, low, high);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

int main()
{
    int n = 10000;
    int arr[10000];
    for (short i = 0; i < n; i++)
        arr[i] = n - i;

    unsigned count = quick_sort_start(arr, 0, n - 1);
    printArr(arr, 0, n - 1);
    cout << "Sorted array in " << count << " microsec or " << count / 1000. << " milisec\n";

    return 0;
}