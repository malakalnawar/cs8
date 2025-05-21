//
// Created by Elijah Ghossein on 5/20/25.
//

#ifndef SMNODE_H
#define SMNODE_H

#include <unordered_map>

class SMNode {

    std::unordered_map<char, SMNode*> edges;

public:

    SMNode();

    [[nodiscard]] SMNode* next(char c) const;
    void addEdge(char c, SMNode* n);

};



#endif //SMNODE_H
