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

void merge(int arr[], int low, int high)
{
    const int mid = (low + high) / 2;
    const int n = high - low + 1;

    int i1 = low;
    int i2 = mid + 1;
    int i3 = 0;
    int temp[n];

    while (i1 <= mid && i2 <= high)
    {
        if (arr[i1] < arr[i2])
            temp[i3++] = arr[i1++];
        else
            temp[i3++] = arr[i2++];
    }
    while (i1 <= mid)
        temp[i3++] = arr[i1++];
    while (i2 <= high)
        temp[i3++] = arr[i2++];

    for (int i = low; i <= high; i++)
        arr[i] = temp[i - low];
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, high);
    }
}

unsigned merge_sort_start(int arr[], int low, int high)
{
    auto start = high_resolution_clock::now();

    mergeSort(arr, low, high);

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

    unsigned count = merge_sort_start(arr, 0, n - 1);
    printArr(arr, 0, n - 1);
    cout << "Sorted array in " << count << " microsec or " << count / 1000. << " milisec\n";

    return 0;
}