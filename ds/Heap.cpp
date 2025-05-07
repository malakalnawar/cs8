//
// Created by Elijah Ghossein on 4/23/25.
//

#ifndef HEAP_CPP
#define HEAP_CPP

#include "Heap.h"

template<typename T>
Heap<T>::Heap(std::initializer_list<T> list) {
    for (auto t : list) {
        push(t);
    }
}

template<typename T>
int Heap<T>::getParentIndex(int childIndex) {
    if ((childIndex - 1) / 2 < 0) return childIndex;
    return (childIndex - 1) / 2;
}

template<typename T>
int Heap<T>::getLeftChildIndex(int parentIndex) {
    if (parentIndex * 2 + 1 >= heap.size())
        return -1;
    return parentIndex * 2 + 1;
}

template<typename T>
int Heap<T>::getRightChildIndex(int parentIndex) {
    if (parentIndex * 2 + 2 >= heap.size())
        return -1;
    return parentIndex * 2 + 2;
}

template<typename T>
int Heap<T>::getMaxChild(int parentIndex) {
    int left = getLeftChildIndex(parentIndex);
    int right = getRightChildIndex(parentIndex);
    if (left == -1 && right == -1) return -1;
    if (left == -1) return right;
    if (right == -1) return left;
    return heap[left] < heap[right] ? right : left;
}

template<typename T>
void Heap<T>::reheapifyDown(int parentIndex) {
    int maxChildIndex = getMaxChild(parentIndex);
    if (maxChildIndex == -1) return;

    if (heap[parentIndex] < heap[maxChildIndex]) {
        std::swap(heap[parentIndex], heap[maxChildIndex]);
        reheapifyDown(maxChildIndex);
    }
}

template<typename T>
void Heap<T>::reheapifyUp(int childIndex) {
    if (childIndex <= 0) return;
    int parentIndex = getParentIndex(childIndex);

    if (heap[parentIndex] < heap[childIndex]) {
        std::swap(heap[parentIndex], heap[childIndex]);
        reheapifyUp(parentIndex);
    }
}

template<typename T>
void Heap<T>::push(T data) {
    heap.push_back(data);
    reheapifyUp(heap.size() - 1);
}

template<typename T>
void Heap<T>::pop() {
    std::swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    reheapifyDown(0);
}

template<typename T>
T Heap<T>::top() const {
    return heap[0];
}

template<typename T>
bool Heap<T>::empty() const {
    return heap.size() == 0;
}

template<typename T>
int Heap<T>::size() const {
    return heap.size();
}

template<typename T>
void Heap<T>::print() const {
    for (auto t : heap) {
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

#endif //HEAP_CPP
