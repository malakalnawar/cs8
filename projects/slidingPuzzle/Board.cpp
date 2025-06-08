//
// Created by Elijah Ghossein on 5/1/25.
//

#include "Board.h"
#include <utility>

// constructor for model class
Board::Board(bool fifteen)
{
    initialize(fifteen);

    // swap tiles
    for (int row = 0; row < BOARD_SIZE; row++) {
      for (int col = 0; col < BOARD_SIZE; col++) {
        Tile& t = board[row][col];
          t.onClick([this, &t] {
              for (auto s : swapables) {
                if (t.getPos() == s->getPos() && !swapping) {
                    if (swapping) return;
                    swapping = true;
                    logSwap(t.getVal()); // log the swap
                    return;
                  }
              }
          });
      }
    }
}



sf::Vector2f Board::getBoardPos() const {
    return {boardPos, boardPos};
}

sf::Vector2f Board::getBoardSize() const {

    float xSize = tileSize * BOARD_SIZE + 10.f * (BOARD_SIZE - 1);
    float ySize = tileSize * BOARD_SIZE + 10.f * (BOARD_SIZE - 1);

    return {xSize, ySize};
}

void Board::updateSwapables() {
    swapables.clear();
    const coord ec = emptyTile->getPos();
    // std::cout << "[" << std::endl;
    for (auto c : nav) {
        coord targetPos = c + ec;
        if (inBounds(targetPos)) {
            Tile& t = board[targetPos.y][targetPos.x];
            swapables.push_back(&t);
            // std::cout << t.getVal() << std::endl;
        }
    }
    // std::cout << "]" << std::endl;
}

bool Board::inBounds(coord c) const {
  return (c.y >= 0 && c.y < BOARD_SIZE && c.x >= 0 && c.x < BOARD_SIZE);
}

void Board::initialize(bool fifteen) {
    BOARD_SIZE = fifteen ? 4 : 3;

    int val = 1; // tile value
    for (int row = 0; row < BOARD_SIZE; ++row) {
        std::vector<Tile> r; // empty row
        for (int col = 0; col < BOARD_SIZE; ++col) {

            if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) val = 0;

            Tile tile({row, col}, val); // creating a new tile
            tile.setSize({tileSize, tileSize}); // set sizec

            // set position
            tile.setPosition({
                boardPos + (tileSize * col + 10.f * col) ,
                boardPos + (tileSize * row + 10.f * row)
            });

            if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) tile.setFillColor(sf::Color::Transparent);

            ++val; // increment tile value
            r.emplace_back(tile); // add to row
        }
        board.emplace_back(r); // add row to board
        if (row == BOARD_SIZE - 1)
            emptyTile = &board[row][BOARD_SIZE - 1]; // create a reference to the empty tile
    }

    updateSwapables(); // update which tiles can be swapped
}

void Board::randomSwapper(int count) {

    if (swapping) return;
    swapping = true;

    enabled = false; // disable the board

    // clone the board
    Board* temp = clone();
    clonedBoard = temp;

    int previous = -1;

    // do multiple swaps
    for (int i = 0; i < count; i++) {


        int max = clonedBoard->swapables.size();
        int r = rand() % max;
        Tile* tile = clonedBoard->swapables[r];

        while (tile->getVal() == previous) {
            max = clonedBoard->swapables.size();
            r = rand() % max;
            tile = clonedBoard->swapables[r];
        }
        previous = tile->getVal();

        logSwap(tile->getVal());

        clonedBoard->swapTile(*tile, false);


    }

    // delete the clone
    delete clonedBoard;

    enabled = true; // enable the board
}

void Board::swapTile(Tile& tile, const bool log) {
    // Store their current grid positions
    auto [r_tile, c_tile] = tile.getPos();
    auto [r_empty, c_empty] = emptyTile->getPos();
    // Update each tile's internal grid coord
    tile.setPos({r_empty, c_empty});
    emptyTile->setPos({r_tile, c_tile});

    if (log) {
        constexpr int totalFrames = 4;
        const float currentX = boardPos + (tileSize * c_tile + 10.f * c_tile);
        const float currentY = boardPos + (tileSize * r_tile + 10.f * r_tile);
        const float targetX = boardPos + (tileSize * c_empty + 10.f * c_empty);
        const float targetY = boardPos + (tileSize * r_empty + 10.f * r_empty);
        const float dx = (targetX - currentX) / static_cast<float>(totalFrames);
        const float dy = (targetY - currentY) / static_cast<float>(totalFrames);
        for (int i = 1; i <= totalFrames; ++i) {
            logFrame(emptyTile, currentX + dx * i, currentY + dy * i);
            logFrame(&tile, targetX - dx * i, targetY - dy * i);
        }
    }

    coord emptyPos = emptyTile->getPos();
    std::swap(board[r_tile][c_tile], *emptyTile);
    emptyTile = &board[emptyPos.y][emptyPos.x];

    updateSwapables(); // update which tiles can be swapped
}

void Board::processFrame() {

    if (!enabled) return;

    if (swapping && frames.empty()) {
        takeAStep();
    }

    for (int i = 0; i < 2 && !frames.empty(); ++i) {
        frame f = frames.front();
        frames.pop_front();
        f.tile->setPosition({f.tx, f.ty});
    }
}

void Board::takeAStep() {
    if (swaps.empty()) {
        swapping = false;
        return;
    }

    swap s = swaps.front();
    swaps.pop_front();

    if (s.val == 0) return;
    Tile* tile = getTileByVal(s.val);

    swapTile(*tile, true);
}

Tile* Board::getTileByVal(int value) {
    for (auto& row : board) {
        for (auto& t : row) {
            if (t.getVal() == value) {
                return &t;
            }
        }
    }
    return nullptr;
}


void Board::logFrame(Tile* t, float x, float y) {
    frame f;
    f.tile = t;
    f.tx = x;
    f.ty = y;
    frames.push_back(f);
}

void Board::logSwap(int v) {
    swap s;
    s.val = v;
    swaps.push_back(s);
}


void Board::setTextures(const std::vector<sf::Texture *> &t) {

    textures = t;

    int val = 1; // tile value
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) break;
            Tile& tile = board[row][col];
            if (val != 0) tile.setTexture(textures[val - 1]); // set texture
            ++val; // increment tile value
        }
   }
}

Board* Board::clone() const {
    Board* copy = new Board(*this); // invokes the copy constructor
    // adjust emptyTile to point to the correct tile in the cloned board
    coord emptyPos = this->emptyTile->getPos();
    copy->emptyTile = &copy->board[emptyPos.y][emptyPos.x];
    // rebuild swapables for the new board
    copy->updateSwapables();
    return copy;
}

std::vector<std::vector<int>> Board::getCurrentState() const {
    std::vector<std::vector<int>> state;
    std::vector<int> r;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        r.clear();
        for (int col = 0; col < BOARD_SIZE; ++col) {
            r.emplace_back(board[row][col].getVal());
        }
        state.emplace_back(r);
    }
    return state;
}

void Board::printCurrentState() const {
    std::vector<std::vector<int>> state = getCurrentState();
    std::cout << std::endl;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::cout << state[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

