//
// Created by Dave Smith on 4/2/25.
//

#ifndef TREENODE_H
#define TREENODE_H
template<typename T>
struct TreeNode
{
    T data;
    TreeNode<T> *left = nullptr, *right = nullptr;
};
#endif //TREENODE_H
