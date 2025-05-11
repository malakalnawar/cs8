//
// Created by Elijah Ghossein on 5/11/25.
//

#ifndef WORD_H
#define WORD_H
#include <Malena/Graphics/Text.h>

#include "SFML/Graphics/Text.hpp"


class Word : public ml::Text {

    int priority;

public:

    Word(const std::string &text);

    void setPriority(int p);
    int getPriority() const;

    bool operator<(const Word &other) const { return priority < other.priority; }
    bool operator==(const Word &other) const { return priority == other.priority; }
    bool operator!=(const Word &other) const { return priority != other.priority; }
    bool operator>(const Word &other) const { return priority > other.priority; }

};



#endif //WORD_H
