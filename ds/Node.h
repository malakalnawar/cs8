//
// Created by Elijah Ghossein on 3/18/25.
//

#ifndef NODE_H
#define NODE_H


template<typename T>
struct Node {
    T data;
    Node* next = nullptr;
    Node* prev = nullptr;
};



#endif //NODE_H
