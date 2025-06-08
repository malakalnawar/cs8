//
// Created by Elijah Ghossein on 5/28/25.
//

#ifndef GAMELAUNCHER_H
#define GAMELAUNCHER_H
#include "../autocorrect/AutoCorrectApp.h"

class GameLauncher : public AutoCorrectApp {

public:

    GameLauncher();

    void registerEvents() override;
};



#endif //GAMELAUNCHER_H
