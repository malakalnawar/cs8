//
// Created by Elijah Ghossein on 5/20/25.
//

#include "SMNode.h"

SMNode::SMNode() = default;

SMNode * SMNode::next(char c) const {
    if (edges.contains(c)) {
        return edges.at(c);
    }
    return nullptr;
}

void SMNode::addEdge(char c, SMNode* n) {
    edges.insert_or_assign(c, n);
}
