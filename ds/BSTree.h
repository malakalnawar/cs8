//
// Created by Dave Smith on 4/2/25.
//

#ifndef BSTREE_H
#define BSTREE_H

#include "TreeNode.h"
#include <initializer_list>
#include <iostream>
#include <queue>
#include <functional>

template <typename T>
class BSTree {

    TreeNode<T> * root;

    void copy(TreeNode<T>* node);
    void push(TreeNode<T>* node, const T& data);
    void pop(TreeNode<T>* node);

    void inorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});
    void preorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});
    void postorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});
    void breadthorder(TreeNode<T>* node, std::function<void(T&)> f = [](T& data){std::cout << data;});

public:
    BSTree(std::initializer_list<T> list);
    BSTree();
    BSTree(const BSTree& tree);

    ~BSTree();

    BSTree& operator=(const BSTree& tree);

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


#include "BSTree.tpp"

#endif //BSTREE_H
