//
// Created by Elijah Ghossein on 4/9/25.
//

#pragma once

template<typename T>
void AVLTree<T>::copy(TreeNode<T> *node)
{
    if (node == nullptr) return;
    push(node->data);
    copy(node->left);
    copy(node->right);
}

template<typename T>
AVLTree<T>::AVLTree(std::initializer_list<T> list)
{
  root = nullptr;
  for (const T& item : list) {
    push(item);
  }
}

template<typename T>
AVLTree<T>::AVLTree()
{
    root = nullptr;
}

template<typename T>
AVLTree<T>::AVLTree(const AVLTree &tree)
{
    root = nullptr;
    copy(tree.root);
}

template<typename T>
AVLTree<T>::~AVLTree()
{
    clear();
}

template<typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree &tree)
{
    if (this != &tree) {
      clear();
      copy(tree.root);
    }
    return *this;
}

template<typename T>
void AVLTree<T>::push(const T &data) {
    push(root, data);
}

template<typename T>
void AVLTree<T>::push(TreeNode<T>* node, const T &data)
{
    if (node == nullptr) {
        node = new TreeNode<T>;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        if (root == nullptr) {
          root = node;
        }
        return;
    }
    if (data <= node->data) {
        if (node->left == nullptr) {
          node->left = new TreeNode<T>{data, nullptr, nullptr};
        } else {
          push(node->left, data);
        }
    } else {
      if (node->right == nullptr) {
        node->right = new TreeNode<T>{data, nullptr, nullptr};
      } else {
        push(node->right, data);
      }
    }
}

template<typename T>
void AVLTree<T>::pop(TreeNode<T> *node) {
    clear();
}


template<typename T>
void AVLTree<T>::pop()
{
    pop(root);
}

template<typename T>
void AVLTree<T>::inorder(TreeNode<T> *node, std::function<void(T&)> f) {
    if (node == nullptr) return;
    inorder(node->left, f); // Left
    f(node->data); // Parent
    inorder(node->right, f); // Right
}

template<typename T>
void AVLTree<T>::inorder(std::function<void(T&)> f)
{
    inorder(root, f);
}

template<typename T>
template<typename U>
void AVLTree<T>::inorder(std::function<void(T&)> f, U& obj)
{
    auto func = [f, &obj](T& data)
    {
        f(data);
    };
    inorder(func);
}

template<typename T>
void AVLTree<T>::preorder(TreeNode<T> *node, std::function<void(T&)> f) {
    if (node == nullptr) {
        return;
    }
    f(node->data); // Parent
    inorder(node->left, f); // Left
    inorder(node->right, f); // Right
}

template<typename T>
void AVLTree<T>::preorder(std::function<void(T&)> f)
{
    preorder(root, f);
}

template<typename T>
template<typename U>
void AVLTree<T>::preorder(std::function<void (T &data)> f, U& obj)
{
    auto func = [obj, f, this](T& data)
    {
        f(data);
    };
    preorder(func);
}

template<typename T>
void AVLTree<T>::postorder(TreeNode<T> *node, std::function<void(T&)> f) {
    if (node == nullptr) {
        return;
    }
    inorder(node->left, f); // Left
    inorder(node->right, f); // Right
    f(node->data); // Parent
}

template<typename T>
void AVLTree<T>::postorder(std::function<void(T&)> f)
{
    postorder(root, f);
}

template<typename T>
template<typename U>
void AVLTree<T>::postorder(std::function<void (T &data)> f, U& obj)
{
    auto func = [obj, f, this](T& data)
    {
        f(data);
    };
    postorder(func);
}

template<typename T>
void AVLTree<T>::breadthorder(TreeNode<T> *node, std::function<void(T&)> f) {
    if (node == nullptr) return;

    std::queue<TreeNode<T>*> q;
    q.push(node);
    while (!q.empty()) {
        TreeNode<T>* current = q.front();
        q.pop();
        f(current->data);
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

template<typename T>
void AVLTree<T>::breadthorder(std::function<void(T&)> f)
{
    breadthorder(root, f);
}

template<typename T>
template<typename U>
void AVLTree<T>::breadthorder(std::function<void (T &data)> f, U& obj)
{
    auto func = [obj, f, this](T& data) {
        f(data);
    };
    breadthorder(func);
}

template<typename T>
void AVLTree<T>::clear()
{
  std::function<void(TreeNode<T>*)> deleteNodes = [&](TreeNode<T> *node) {
    if (node == nullptr) return;
    deleteNodes(node->left);
    deleteNodes(node->right);
    delete node;
  };
  deleteNodes(root);
  root = nullptr;
}
