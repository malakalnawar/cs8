//
// Created by Elijah Ghossein on 3/19/25.
//

#ifndef R_NODEITERATOR_H
#define R_NODEITERATOR_H

#include <iterator>
#include "Node.h"

template<typename T>
class R_NodeIterator {

    Node<T> *current;

public:

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    R_NodeIterator(Node<T> *current);
    // Bi-directional iterator
    R_NodeIterator &operator++(); // Prefix
    R_NodeIterator operator++(int); // Postfix
    R_NodeIterator &operator--(); // Prefix
    R_NodeIterator operator--(int); // Postfix

    bool operator==(const R_NodeIterator<T> &other) const;
    bool operator!=(const R_NodeIterator<T> &other) const;

    const T &operator*() const; // Constant Dereference
    T &operator*(); // Dereference
};

#include "R_NodeIterator.tpp"

#endif //R_NODEITERATOR_H
