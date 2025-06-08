//
// Created by Elijah Ghossein on 5/21/25.
//

#include "slidingPuzzleApp.h"

slidingPuzzleApp::slidingPuzzleApp(bool fifteen)
    : Application(720, 720, 32, "Sliding Puzzle"),
    board(fifteen), controller(&board, fifteen)
{

    ml::FontManager::loadFontFromFile("sfc", "../fonts/sixty-four-convergence/SixtyfourConvergence.ttf");
    const sf::Font& font = ml::FontManager::getDefault();
    loadTextures();
    board.setTextures(textures);

    // add board components
    Application::addComponent(board);
    for (int i = 0; i < board.board.size(); i++) {
        for (int j = 0; j < board.board[i].size(); j++) {
            Application::addComponent(board.board[i][j]);
        }
    }
    // add board controller components
    Application::addComponent(controller.randomize);
    Application::addComponent(controller.solve);

    if (fifteen) {
        p = {15, 11, 10, 6, 7, 3, 4, 8, 12};
    } else {
        p = {8, 5, 6, 3, 2, 6, 4, 7, 5, 4};
    }

}

void slidingPuzzleApp::initialization() {
}

void slidingPuzzleApp::registerEvents() {
    // timer
    board.onUpdate([this] {
        board.processFrame();
    });

    board.onKeypress([this]() {
        // board.printCurrentState();
        // if (board.swapping) return;
        // board.swapping = true;
        // for (int i = 0; i < p.size(); i++) {
        //     board.logSwap(p[i]);
        // }
        // p.clear();
    });
}

void slidingPuzzleApp::loadTextures() {
    const bool texturesLoaded =
            tile1.loadFromFile("../img/slidingPuzzle/tile01.png") &&
            tile2.loadFromFile("../img/slidingPuzzle/tile02.png") &&
            tile3.loadFromFile("../img/slidingPuzzle/tile03.png") &&
            tile4.loadFromFile("../img/slidingPuzzle/tile04.png") &&
            tile5.loadFromFile("../img/slidingPuzzle/tile05.png") &&
            tile6.loadFromFile("../img/slidingPuzzle/tile06.png") &&
            tile7.loadFromFile("../img/slidingPuzzle/tile07.png") &&
            tile8.loadFromFile("../img/slidingPuzzle/tile08.png") &&
            tile9.loadFromFile("../img/slidingPuzzle/tile09.png") &&
            tile10.loadFromFile("../img/slidingPuzzle/tile10.png") &&
            tile11.loadFromFile("../img/slidingPuzzle/tile11.png") &&
            tile12.loadFromFile("../img/slidingPuzzle/tile12.png") &&
            tile13.loadFromFile("../img/slidingPuzzle/tile13.png") &&
            tile14.loadFromFile("../img/slidingPuzzle/tile14.png") &&
            tile15.loadFromFile("../img/slidingPuzzle/tile15.png");
    if (!texturesLoaded)
    {
        throw std::runtime_error("Failed to load one or more textures.");
    }
    textures = {
        &tile1, &tile2, &tile3, &tile4, &tile5,
        &tile6, &tile7, &tile8, &tile9, &tile10,
        &tile11, &tile12, &tile13, &tile14, &tile15
    };
}
