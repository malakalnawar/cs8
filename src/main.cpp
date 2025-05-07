#include <iostream>
#include "../algorithms/QuickSort.h"

int main() {
    int arr[] = {9, 3, 7, 5, 6, 4, 8, 2, 5, 78, 4, 1};
    int size = 11;

    quickSort(arr, 0, size - 1);

    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';

    return 0;
}