//
// Created by Elijah Ghossein on 5/26/25.
//

#ifndef ASTAR_H
#define ASTAR_H

#include <vector>

#include "../projects/slidingPuzzle/Tile.h"

// state represents a board configuration in the 8-puzzle
struct state {
    std::vector<std::vector<int>> board; // board
    int boardSize = 0;
    int g = 0; // cost from start node
    int h = 0; // heuristic value
    int f = 0; // total estimated cost (g + h)
    const state* parent = nullptr; // pointer to parent node (used for path reconstruction)
    bool operator==(const state& other) const {
        return board == other.board;
    }
    bool operator<(const state& other) const {
        return board < other.board;
    }
    // constructor
    state(std::vector<std::vector<int>> b) : board(b) {boardSize = board.size();}
};

struct CompareStates {
    bool operator()(const state* a, const state* b) const {
        return a->f > b->f;
    }
};

coord findZero(const state& s);

int manhattanDistance(const state& s, const state& g);

int customHeuristic(const state& s, const state& g);

std::vector<state> getChildren(const state& s);

std::vector<state> reconstruct(const state* s);

std::vector<int> aStar(state start, state goal, int (*heuristic)(const state& s, const state& g));

#endif //ASTAR_H
