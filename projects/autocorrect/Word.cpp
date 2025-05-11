//
// Created by Elijah Ghossein on 5/11/25.
//

#include "Word.h"

Word::Word(const std::string& text)
    : priority(0)
{
    setString(text);
}

void Word::setPriority(int p) {
    priority = p;
}

int Word::getPriority() const {
    return priority;
}
