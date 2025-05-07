//
// Created by Elijah Ghossein on 5/6/25.
//

#include "MergeSort.h"

#include <algorithm>

void mergeSort(int *arr, int size) {
    if (size <= 1) return;

    int leftSize = size / 2;
    int rightSize = size - leftSize;

    mergeSort(arr, leftSize);
    mergeSort(arr + leftSize, rightSize);

    merge(arr, leftSize, rightSize);
}

void merge(int *arr, int leftSize, int rightSize) {

    int totalSize = leftSize + rightSize; // total size
    int* temp = new int[totalSize]; // temp array

    int leftCopied = 0, rightCopied = 0, totalCopied = 0; // pointers

    int* leftHalf = arr; // left array
    int* rightHalf = arr + leftSize; // right array

    // compare elements in left and right, input smallest in temp, increment pointer
    while (leftCopied < leftSize && rightCopied < rightSize) {
        if (leftHalf[leftCopied] <= rightHalf[rightCopied]) {
            temp[totalCopied++] = leftHalf[leftCopied++];
        } else {
            temp[totalCopied++] = rightHalf[rightCopied++];
        }
    }

    // copy remaining items from left to temp
    while (leftCopied < leftSize) {
        temp[totalCopied++] = leftHalf[leftCopied++];
    }
    // copy remaining items from right to temp
    while (rightCopied < rightSize) {
        temp[totalCopied++] = rightHalf[rightCopied++];
    }
    // copy temp back to array
    for (int i = 0; i < totalSize; ++i) {
        arr[i] = temp[i];
    }
    // delete temp to free up memory
    delete[] temp;

}