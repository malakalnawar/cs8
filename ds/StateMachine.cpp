//
// Created by Elijah Ghossein on 5/20/25.
//

#include "StateMachine.h"

StateMachine::StateMachine() : start(new SMNode), validate(new SMNode) {

    for (int i = 48; i <= 57; i++) {
        char c = static_cast<char>(i);
        start->addEdge(c, validate);
        validate->addEdge(c, validate);
    }
    for (int i = 65; i <= 90; i++) {
        char c = static_cast<char>(i);
        start->addEdge(c, validate);
        validate->addEdge(c, validate);
    }
    for (int i = 97; i <= 122; i++) {
        char c = static_cast<char>(i);
        start->addEdge(c, validate);
        validate->addEdge(c, validate);
    }
    char c = 95;
    start->addEdge(c, validate);
    validate->addEdge(c, validate);
}

bool StateMachine::valid(const std::string &str) {

    char c1 = str[0];
    SMNode* node = start->next(c1);
    if (node == nullptr) {
        return false;
    }

    for (int i = 1; i < str.size(); i++) {
        char c = str[i];
        node = node->next(c);
        if (node == nullptr) {
            return false;
        }
    }

    return true;
}
