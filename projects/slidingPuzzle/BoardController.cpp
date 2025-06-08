//
// Created by Elijah Ghossein on 5/26/25.
//

#include "BoardController.h"

#include "../../algorithms/AStar.h"

BoardController::BoardController(Board *board, bool fifteen)
    : board(board)
{
    if (!fifteen) {
        goal = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };
    } else {
        goal = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 0},
        };
    }
    setup();
    randomize.onClick([this, board]() {
        board->randomSwapper(250);
    });
    solve.onClick([this, board]() {
        solveBoard();
    });
}

void BoardController::solveBoard() {

    state s = state(board->getCurrentState());
    state g = state(goal);

    // std::cout << "Manhattan Distance:" << std::endl;
    // const std::vector<int> path0 = aStar(s, g, manhattanDistance);

    std::cout << "Custom Heuristic:" << std::endl;
    const std::vector<int> path1 = aStar(s, g, customHeuristic);

    // if (path0.empty()) {
    //     std::cout << "No solution found." << std::endl;
    //     return;
    // }
    if (path1.empty()) {
        std::cout << "No solution found." << std::endl;
        return;
    }

    if (board->swapping) return;
    board->swapping = true;

    for (int i = 0; i < path1.size(); i++) {
        board->logSwap(path1[i]); // log the swap
    }
}

void BoardController::setup() {
    float xPos = board->getBoardPos().x;
    float yPos = board->getBoardPos().y + board->getBoardSize().y + 20.f;
    float xSize = board->getBoardSize().x;
    float ySize = 40.f;

    randomize.setFillColor({70, 70, 70, 200});
    randomize.setPosition({xPos, yPos});
    randomize.setSize({xSize, ySize});
    randomize.setString("Randomize");

    solve.setFillColor({70, 70, 70, 200});
    solve.setPosition({xPos, yPos + ySize + 10.f});
    solve.setSize({xSize, ySize});
    solve.setString("Solve");
}
