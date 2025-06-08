//
// Created by Elijah Ghossein on 3/19/25.
//

#pragma once

template<typename T>
R_NodeIterator<T>::R_NodeIterator(Node<T> *current) : current(current) {

}

template<typename T>
R_NodeIterator<T> & R_NodeIterator<T>::operator++() {
    current = current->prev;
    return *this;
}

template<typename T>
R_NodeIterator<T> R_NodeIterator<T>::operator++(int) {
    R_NodeIterator<T> *temp = *this;
    current = current->prev;
    return temp;
}

template<typename T>
R_NodeIterator<T> & R_NodeIterator<T>::operator--() {
    current = current->next;
    return *this;
}

template<typename T>
R_NodeIterator<T> R_NodeIterator<T>::operator--(int) {
    R_NodeIterator<T> *temp = *this;
    current = current->next;
    return temp;
}

template<typename T>
bool R_NodeIterator<T>::operator==(const R_NodeIterator<T> &other) const {
    return other.current == current;
}

template<typename T>
bool R_NodeIterator<T>::operator!=(const R_NodeIterator<T> &other) const {
    return other.current != current;
}

template<typename T>
const T & R_NodeIterator<T>::operator*() const {
    return current->data;
}

template<typename T>
T &R_NodeIterator<T>::operator*() {
    return current->data;
}

