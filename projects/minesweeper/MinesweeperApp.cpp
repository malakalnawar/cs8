//
// Created by Elijah Ghossein on 5/1/25.
//

#include "minesweeperApp.h"
#include "Model.h"
#include "Malena/Utilities/TextureSlicer.h"
#include <future>
#include <atomic>

MinesweeperApp::MinesweeperApp(int c, int r, int b)
    : Application(1024, 1024, 32, "minesweeper - Backtracking"),
      board(c, r, b),
      backtracker(&board)
{
}

void MinesweeperApp::initialization()
{
    ml::FontManager::loadFontFromFile("sfc", "../fonts/sixty-four-convergence/SixtyfourConvergence.ttf");
    const sf::Font& font = ml::FontManager::getDefault();

    const bool texturesLoaded =
            tileUnknown.loadFromFile("../img/minesweeper/TileUnknown.png") &&
            tile1.loadFromFile("../img/minesweeper/Tile1.png") &&
            tile2.loadFromFile("../img/minesweeper/Tile2.png") &&
            tile3.loadFromFile("../img/minesweeper/Tile3.png") &&
            tile4.loadFromFile("../img/minesweeper/Tile4.png") &&
            tile5.loadFromFile("../img/minesweeper/Tile5.png") &&
            tile6.loadFromFile("../img/minesweeper/Tile6.png") &&
            tile7.loadFromFile("../img/minesweeper/Tile7.png") &&
            tile8.loadFromFile("../img/minesweeper/Tile8.png") &&
            tileEmpty.loadFromFile("../img/minesweeper/TileEmpty.png") &&
            tileExploded.loadFromFile("../img/minesweeper/TileExploded.png") &&
            tileFlag.loadFromFile("../img/minesweeper/TileFlag.png") &&
            tileMine.loadFromFile("../img/minesweeper/TileMine.png");

    if (!texturesLoaded)
    {
        throw std::runtime_error("Failed to load one or more textures.");
    }

    textures = {
        &tileEmpty, &tile1, &tile2, &tile3, &tile4, &tile5,
        &tile6, &tile7, &tile8, &tileFlag, &tileMine, &tileExploded, &tileUnknown
    };
    // set all tile textures
    for (Node& node : board)
    {
        node.setTexture(&tileUnknown);
        addComponent(node);
    }
    board.setTextures(textures); // give board access to texture references
    board.setFont(font);

    // invisible component for key listening
    auto* keyListener = new ml::Rectangle();
    keyListener->onKeypress([this] {
        if (hoveredNode)
        {
            auto [x,y] = hoveredNode->getPos();
            board.toggleNodeFlag(x, y);
        }

        // backtracker.takeAStep();

        // Note for dave
        int total = board.getNonBombCount();
        srand(time(nullptr));
        for (int i = 0; i < total; i++)
        {
            int x = rand() % static_cast<int>(sqrt(total));
            int y = rand() % static_cast<int>(sqrt(total));
            Node& node = board.getNode(x, y);
            if (node.getVal() != 11)
            {
                coordinates pos = node.getPos();
                board.pressNode(pos, textures);
                board.updateNodeCombinations();
            }
        }
    });
    addComponent(*keyListener);

    // Backtracker
    backtracker.initialize(font);
    addComponent(backtracker.current);
    addComponent(backtracker.flagButton);

    // Loser text
    addComponent(board.loserText);
}

void MinesweeperApp::registerEvents()
{
    for (Node& node : board)
    {
        node.onClick([&node, this] {
            coordinates pos = node.getPos();
            board.pressNode(pos, textures);
            board.updateNodeCombinations();
        });

        node.onHover([&node, this] {
            hoveredNode = &node;
        });
    }


    backtracker.flagButton.onClick([this] {
        if (this->flagButtonInteractionClock.getElapsedTime() < this->clickDebounceTime)
        {
            // nit enough time has passed since the last processed click for this button so ignore this current event
            return;
        }
        //std::thread([this] {
        //    if (backtracker.solve()) {
        //        std::cout << "solved" << std::endl;
        //    }
        //}).detach();

        this->flagButtonInteractionClock.restart();
    });

    // timer
    backtracker.current.onUpdate([this] {
        ++frames;
        if (frames % 5 == 0)
        {
            //
            backtracker.takeAStep();
        }
    });
}
