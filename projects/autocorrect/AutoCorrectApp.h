//
// Created by Elijah Ghossein on 5/10/25.
//

#ifndef AUTOCORRECTAPP_H
#define AUTOCORRECTAPP_H
#include <Malena/Application/Application.h>

#include "SMValidator.h"
#include "TextBox.h"
#include "WordSort.h"


class AutoCorrectApp : public ml::Application
{

public:

    TextBox textBox;
    WordSort autocorrect;
    SMValidator validator;

    AutoCorrectApp();

    void initialization() override;

    void registerEvents() override;
};



#endif //AUTOCORRECTAPP_H
