//
// Created by Elijah Ghossein on 3/19/25.
//

#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include <iterator>
#include "Node.h"

template<typename T>
class NodeIterator {

    Node<T>* current;

public:

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    NodeIterator(Node<T>* current);

    Node<T>* get_node() const;

    // Bi-directional iterator
    NodeIterator& operator++(); // Prefix
    NodeIterator operator++(int); // Postfix
    NodeIterator& operator--(); // Prefix
    NodeIterator operator--(int); // Postfix

    bool operator==(const NodeIterator<T>& other) const;
    bool operator!=(const NodeIterator<T>& other) const;

    const T &operator*() const; // Constant Dereference
    T &operator*(); // Dereference
};

#include "NodeIterator.tpp"

#endif //NODEITERATOR_H
