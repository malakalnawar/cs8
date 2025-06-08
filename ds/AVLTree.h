//
// Created by Elijah Ghossein on 4/9/25.
//

#ifndef AVLTREE_H
#define AVLTREE_H

#include "TreeNode.h"
#include <initializer_list>
#include <iostream>
#include <queue>
#include <functional>

template <typename T>
class AVLTree {

    TreeNode<T> * root;

    void copy(TreeNode<T>* node);
    void push(TreeNode<T>* node, const T& data);
    void pop(TreeNode<T>* node);

    void inorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});
    void preorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});
    void postorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});
    void breadthorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});

public:

    AVLTree(std::initializer_list<T> list);
    AVLTree();
    AVLTree(const AVLTree& tree);

    ~AVLTree();

    AVLTree& operator=(const AVLTree& tree);

    void push(const T& data);
    void pop();

    void inorder(std::function<void(T&)> f = [](T& data){std::cout << data;});
    template<typename U>
    void inorder(std::function<void(T&)> f, U& obj);

    void preorder(std::function<void(T&)> f = [](T& data){std::cout << data;});
    template<typename U>
    void preorder(std::function<void (T &data)> f, U& obj);

    void postorder(std::function<void(T&)> f = [](T& data){std::cout << data;});
    template<typename U>
    void postorder(std::function<void (T &data)> f, U& obj);

    void breadthorder(std::function<void(T&)> f = [](T& data){std::cout << data;});
    template<typename U>
    void breadthorder(std::function<void (T &data)> f, U& obj);

    void clear();

};

#include "AVLTree.tpp"

#endif //AVLTREE_H
