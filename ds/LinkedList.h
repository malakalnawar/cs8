//
// Created by Elijah Ghossein on 3/18/25.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <initializer_list>
#include <ostream>

#include "Node.h"
#include "NodeIterator.h"
#include "R_NodeIterator.h"

template <typename T>
class LinkedList {

    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int _size = 0;
    void push_front(Node<T> *node); // adds data in a node previous to head
    Node<T>* create_node(const T &data); // creates a new node
    void add_first_node(const T &data); // adds the firs node

public:

    LinkedList();
    LinkedList(const std::initializer_list<T>& list);
    LinkedList(const LinkedList<T> &other); // Copy
    ~LinkedList();

    using iterator = NodeIterator<T>;
    using r_iterator = R_NodeIterator<T>;
    iterator begin() const;
    iterator end() const;
    r_iterator r_begin() const;
    r_iterator r_end() const;

    void push_front(const T& data); // adds data in a node previous to head
    [[nodiscard]] bool empty() const; // return true if list is empty, otherwise false
    [[nodiscard]] int size() const; // return the number of node in the list
    void pop_back(); // remove tail node
    void pop_front(); // remove head node
    const T& back() const; // return data in the tail node
    const T& front() const; // return data in the head node
    void push_back(const T& data); // Insert an item at the end of the list
    void insert_before(Node<T>* node, const T& data); // Insert before a specific node
    void insert_after(Node<T>* node, const T& data); // Insert after a specific node
    Node<T>* find(const T& data) const; // Find an item
    void remove(const T& data); // Remove an item by value
    void clear(); // Clear the list

    LinkedList& operator=(const LinkedList<T> &other);
    LinkedList& operator+=(const T &data);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const LinkedList<U>& list);
};

#include "LinkedList.tpp"

#endif //LINKEDLIST_H
