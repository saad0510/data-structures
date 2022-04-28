#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

void printArr(int arr[], int size)
{
    for (short i = 0; i < size; i++)
        printf("%d ", arr[i]);
    puts("");
}

unsigned shell_sort(int arr[], int size)
{
    auto start = high_resolution_clock::now();

    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            // replace 1 with gap in insertion sort
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    return duration.count();
}

int main()
{
    int n = 509;
    int arr[509];
    for (short i = 0; i < n; i++)
        arr[i] = n - i;

    unsigned count = shell_sort(arr, n);
    printArr(arr, n);

    cout << "Sorted array in " << count << " microsec or " << count / 1000. << " milisec\n";

    return 0;
}
