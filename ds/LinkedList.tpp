//
// Created by Elijah Ghossein on 3/18/25.
//

#pragma once
#include "SFML/Window/Joystick.hpp"
#include "SFML/Window/Keyboard.hpp"

/*
 * CONSTRUCTOR
 */

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template<typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T> &list) {
    for (auto &item : list) {
        push_front(item);
    }
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
    : head(nullptr), tail(nullptr)
{
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}


/*
 * PRIVATE
 */

template<typename T>
void LinkedList<T>::push_front(Node<T>* node) {
    node->next = head;
    if (head) head->prev = node;
    head = node;
}

template<typename T>
Node<T> *LinkedList<T>::create_node(const T &data) {
    return new Node<T>{data};
}

template<typename T>
void LinkedList<T>::add_first_node(const T &data) {
    auto *n = new Node<T>;
    head = n;
    n->data = data;
    tail = n;
    n->next = nullptr;
    n->prev = nullptr;
}

/*
 * PUBLIC
 */

/*
 * ITERATOR
 */

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() const {
    return NodeIterator<T>(head);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() const {
    return NodeIterator<T>(nullptr);
}

template<typename T>
typename LinkedList<T>::r_iterator LinkedList<T>::r_begin() const {
    return R_NodeIterator<T>(tail);
}

template<typename T>
typename LinkedList<T>::r_iterator LinkedList<T>::r_end() const {
    return R_NodeIterator<T>(nullptr);
}

/*
 *
 */

template<typename T>
void LinkedList<T>::push_front(const T& data) {
    if (empty())
        add_first_node(data);
    else
        push_front(create_node(data));
    _size++;
}

template<typename T>
bool LinkedList<T>::empty() const {
    return head == nullptr;
}

template<typename T>
int LinkedList<T>::size() const {
    return _size;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (!tail) return;
    if (tail == head) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else {
        Node<T>* prev_t = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete prev_t;
    }
    _size--;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (!head) return;
    if (tail == head) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node<T>* prev_h = head;
        head = head->next;
        head->prev = nullptr;
        delete prev_h;
    }
    _size--;
}

template<typename T>
const T & LinkedList<T>::back() const {
    return tail->data;
}

template<typename T>
const T & LinkedList<T>::front() const {
    return head->data;
}

template<typename T>
void LinkedList<T>::push_back(const T &data) {
    auto *n = new Node<T>;
    n->data = data;
    n->next = nullptr;
    if (empty()) {
        head = n;
        tail = n;
        n->prev = nullptr;
    } else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
    _size++;
}

template<typename T>
void LinkedList<T>::insert_before(Node<T> *node, const T &data) {
    if (node == head) {
        push_front(data);
        return;
    }

    auto *new_node = new Node<T>{data};
    Node<T> *prev_node = node->prev;

    prev_node->next = new_node;
    new_node->prev = prev_node;

    new_node->next = node;
    node->prev = new_node;

    _size++;
}

template<typename T>
void LinkedList<T>::insert_after(Node<T> *node, const T &data) {
    if (node == tail) {
        push_back(data);
        return;
    }

    auto *new_node = new Node<T>{data};
    Node<T> *next_node = node->next;

    node->next = new_node;
    next_node->prev = new_node;

    new_node->prev = node;
    new_node->next = next_node;

    _size++;
}

template<typename T>
Node<T>* LinkedList<T>::find(const T& data) const {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == data) {
            return it.get_node();
        }
    }
    return nullptr;
}

template<typename T>
void LinkedList<T>::remove(const T &data) {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == data) {
            Node<T>* node = it.get_node();
            Node<T>* next_node = node->next;
            Node<T>* prev_node = node->prev;

            if (node == head && node == tail) {
                head = nullptr;
                tail = nullptr;
            }
            else if (node == head) {
                head = next_node;
                if (head) head->prev = nullptr;
            }
            else if (node == tail) {
                tail = prev_node;
                if (tail) tail->next = nullptr;
            }
            else {
                prev_node->next = next_node;
                next_node->prev = prev_node;
            }
            delete node;
            _size--;
            break;
        }
    }
}

template<typename T>
void LinkedList<T>::clear() {
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    _size = 0;
}





template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
    if (this == &other) {
        return *this;
    }
    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }
    return *this;
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator+=(const T &data) {
    push_back(data);
    return *this;
}


template <typename U>
std::ostream& operator<<(std::ostream& out, const LinkedList<U>& list) {
    Node<U> *walker = list.head;
    while (walker) {
        out << walker->data << " ";
        walker = walker->next;
    }
    return out;
}



