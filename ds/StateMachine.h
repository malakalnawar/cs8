//
// Created by Elijah Ghossein on 5/20/25.
//

#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "SMNode.h"

#include <string>

class StateMachine {

    SMNode* start;
    SMNode* validate;

public:

    StateMachine();

    bool valid(const std::string& str);

};



#endif //STATEMACHINE_H
