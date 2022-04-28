#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

unsigned insertion_sort(int arr[], int size)
{
    auto start = high_resolution_clock::now();
    for (int i = 1; i < size; i++)
    {
        const int temp = arr[i];
        int j = i;
        while (j >= 1 && arr[j - 1] > temp)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = temp;
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
    int n = 100;
    int arr[100];
    for (short i = 0; i < n; i++)
        arr[i] = n - i;

    unsigned count = insertion_sort(arr, n);
    printArr(arr, n);

    cout << "Sorted array in " << count << " microsec or " << count / 1000. << " milisec\n";

    return 0;
}