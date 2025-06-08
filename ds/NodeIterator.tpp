//
// Created by Elijah Ghossein on 3/19/25.
//

#pragma once

template<typename T>
NodeIterator<T>::NodeIterator(Node<T> *current) : current(current) {

}

template<typename T>
Node<T> *NodeIterator<T>::get_node() const {
    return current;
}


template<typename T>
NodeIterator<T>& NodeIterator<T>::operator++() {
    current = current->next;
    return *this;
}

template<typename T>
NodeIterator<T> NodeIterator<T>::operator++(int) {
    NodeIterator<T> temp = *this;
    current = current->next;
    return temp;
}

template<typename T>
NodeIterator<T>& NodeIterator<T>::operator--() {
    current = current->prev;
    return *this;
}

template<typename T>
NodeIterator<T> NodeIterator<T>::operator--(int) {
    NodeIterator<T> temp = *this;
    current = current->prev;
    return temp;
}

template<typename T>
bool NodeIterator<T>::operator==(const NodeIterator<T>& other) const {
    return other.current == current;
}

template<typename T>
bool NodeIterator<T>::operator!=(const NodeIterator<T>& other) const {
    return other.current != current;
}

template<typename T>
const T& NodeIterator<T>::operator*() const {
    return current->data;
}

template<typename T>
T& NodeIterator<T>::operator*() {
    return current->data;
}