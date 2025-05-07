//
// Created by Elijah Ghossein on 4/23/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <iostream>

template <typename T>
class Heap {

    std::vector<T> heap;

    int getParentIndex(int childIndex);
    int getLeftChildIndex(int parentIndex);
    int getRightChildIndex(int parentIndex);
    int getMaxChild(int parentIndex);

    void reheapifyDown(int parentIndex);
    void reheapifyUp(int childIndex);

public:

    Heap(std::initializer_list<T> list);

    void push(T data);
    void pop();
    T top() const;
    bool empty() const;
    int size() const;
    void print() const;

};

#include "Heap.cpp"

#endif //HEAP_H
