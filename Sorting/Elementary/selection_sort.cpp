#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

unsigned selection_sort(int arr[], int size)
{
    auto start = high_resolution_clock::now();

    for (int i = 0; i <= size - 2; i++)
    {
        int min = i;
        for (int j = i + 1; j <= size - 1; j++)
            if (arr[j] < arr[min])
                min = j;

        if (min != i)
            swap(arr[i], arr[min]);
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

    unsigned count = selection_sort(arr, n);
    printArr(arr, n);

    cout << "Sorted array in " << count << " microsec or " << count / 1000. << " milisec\n";

    return 0;
}