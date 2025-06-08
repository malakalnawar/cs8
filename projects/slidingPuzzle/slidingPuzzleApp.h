//
// Created by Elijah Ghossein on 5/21/25.
//

#ifndef SLIDINGPUZZLEAPP_H
#define SLIDINGPUZZLEAPP_H
#include "Malena/common.hpp"
#include "Board.h"
#include "BoardController.h"

class slidingPuzzleApp : public ml::Application {

    Board board;
    BoardController controller;

    std::vector<int> p;

    std::vector<sf::Texture*> textures; // container for all textures

    sf::Texture tile1;
    sf::Texture tile2;
    sf::Texture tile3;
    sf::Texture tile4;
    sf::Texture tile5;
    sf::Texture tile6;
    sf::Texture tile7;
    sf::Texture tile8;
    sf::Texture tile9;
    sf::Texture tile10;
    sf::Texture tile11;
    sf::Texture tile12;
    sf::Texture tile13;
    sf::Texture tile14;
    sf::Texture tile15;

    int frames = 0;

    void loadTextures();

public:

    slidingPuzzleApp(bool fifteen);

    void initialization() override;

    void registerEvents() override;
};



#endif //SLIDINGPUZZLEAPP_H
