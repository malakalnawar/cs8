//
// Created by Elijah Ghossein on 5/1/25.
//

#ifndef MINESWEEPERAPP_H
#define MINESWEEPERAPP_H

#include <Malena/common.hpp>

#include "Backtracker.h"
#include "Model.h"


class MinesweeperApp : public ml::Application
{

    Model board; // board
    Backtracker backtracker; // backtracker

    int stepIndex = 0;
    bool playingSteps = false;

    Node* hoveredNode = nullptr; // pointer to node that is being hovered over

    std::vector<sf::Texture*> textures; // container for all textures
    // textures
    sf::Texture tileUnknown;
    sf::Texture tile1;
    sf::Texture tile2;
    sf::Texture tile3;
    sf::Texture tile4;
    sf::Texture tile5;
    sf::Texture tile6;
    sf::Texture tile7;
    sf::Texture tile8;
    sf::Texture tileEmpty;
    sf::Texture tileExploded;
    sf::Texture tileFlag;
    sf::Texture tileMine;

    int frames = 0;

public:

    MinesweeperApp(int c, int r, int b);

    void initialization() override;

    void registerEvents() override;

};



#endif //MINESWEEPERAPP_H
