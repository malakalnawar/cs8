//
// Created by Elijah Ghossein on 5/1/25.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "Tile.h"

struct swap {
    int val;
};

struct frame {
    Tile* tile;
    float tx, ty;
};

class Board : public ml::Rectangle {

    Board* clonedBoard = nullptr;

    int BOARD_SIZE = 0;

    int cols; // number of columns
    int rows; // number of rows
    float boardPos = 50.f; // board screen position
    float tileSize = 75.f; // node size

    Tile* emptyTile = nullptr;

    std::deque<frame> frames;
    std::deque<swap> swaps;

    void logFrame(Tile* t, float x, float y);

    std::vector<coord> nav = { // directional offsets
        {-1,0},
        {0,-1},
        {1,0},
        {0,1}
    };

    std::vector<sf::Texture*> textures; // container for all textures

    void initialize(bool fifteen);

    void swapTile(Tile& tile, bool log);

    std::vector<Tile*> swapables;

    [[nodiscard]] bool inBounds(coord c) const;
    void updateSwapables();

    Board *clone() const;

    Tile* getTileByVal(int value);

public:

    bool swapping = false;
    bool enabled = true;
    std::vector<std::vector<Tile>> board; // game board of nodes, indexed as board[y][x]

    Board(bool fifteen);

    void logSwap(int v);
    std::vector<std::vector<int>> getCurrentState() const;
    void printCurrentState() const;
    void setTextures(const std::vector<sf::Texture *> &t);
    void processFrame();
    void takeAStep();
    void randomSwapper(int count);
    sf::Vector2f getBoardPos() const;
    sf::Vector2f getBoardSize() const;

};



#endif //BOARD_H
