//
// Created by Elijah Ghossein on 5/26/25.
//

#include "AStar.h"

#include <queue>
#include <cmath>
#include <set>

#include "../projects/slidingPuzzle/Tile.h"

// calculate the Manhattan distance heuristic between current and goal states
int manhattanDistance(const state& s, const state& g) {
    int h = 0;
    for (int i = 0; i < s.boardSize; ++i)
        for (int j = 0; j < s.boardSize; ++j)
            if (s.board[i][j] != 0) { // skip empty tile
                for (int x = 0; x < g.boardSize; ++x)
                    for (int y = 0; y < g.boardSize; ++y)
                        if (g.board[x][y] == s.board[i][j])
                            h += std::abs(i - x) + std::abs(j - y); // add tile distance
            }
    return h;
}

//
int customHeuristic(const state &s, const state &g) {
    return manhattanDistance(s, g) * 2.5;
}

// generate all valid childing board configurations by moving the empty tile
std::vector<state> getChildren(const state& s) {
    std::vector<state> children; // children states
    std::vector<coord> swappables; // coordinates of tiles that can be swapped with 0
    auto inBounds = [](coord c, int size) {
        return c.y >= 0 && c.y < size && c.x >= 0 && c.x < size;
    };
    const std::vector<coord> nav = { // directional offsets
        {-1,0},
        {0,-1},
        {1,0},
        {0,1}
    };
    // find the position of the 0
    const coord ec = findZero(s);
    // calculate positions of tiles that can be swapped with
    for (int i = 0; i < nav.size(); ++i) {
        coord c = nav[i] + ec;
        if (inBounds(c, s.boardSize)) {
            swappables.push_back(c);
        }
    }
    // generate children boards and assign the same parent to each
    for (auto c : swappables) {
        auto child = state(s.board);
        const int v = child.board[c.y][c.x];
        child.board[c.y][c.x] = 0;
        child.board[ec.y][ec.x] = v;
        children.push_back(child);
    }
    return children;
}

// trace back from the goal s to the start s
std::vector<state> reconstruct(const state* s) {
    std::vector<state> path;
    const state* e = s;
    while (e != nullptr) {
        path.push_back(*e);
        e = e->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// returns a sequence of tile values that were swapped with 0 to reach the goal.
std::vector<int> aStar(state start, state goal, int (*heuristic)(const state& s, const state& g)) {

    const auto startTime = std::chrono::high_resolution_clock::now();

    // min-heap priority queue sorted by f = g + h
    std::priority_queue<state*, std::vector<state*>, CompareStates> pq;

    // store visited board configurations (uses operator< on state)
    std::set<state> visited;

    // initialize start state's heuristic and f value
    start.h = heuristic(start, goal);
    start.f = start.g + start.h;

    // allocate start node on heap for pointer use
    state* startPtr = new state(start);
    pq.push(startPtr);

    while (!pq.empty()) {

        // get top state (lowest f)
        state* current = pq.top();
        pq.pop();
        /*
         * check if goal is reached
         */
        if (current->board == goal.board) {
            // reconstruct path from start to goal
            std::vector<state> path = reconstruct(current);
            std::vector<int> moves;
            // reconstruct move sequence from path
            for (int i = 1; i < path.size(); ++i) {
                coord prev0 = findZero(path[i - 1]);
                // The tile that was swapped with zero is at the previous zero's location in the current board
                moves.push_back(path[i].board[prev0.y][prev0.x]);
            }
            // testing
            const auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = endTime - startTime;
            std::cout << "Execution time: " << elapsed.count() << " seconds" << std::endl;
            std::cout << "Moves: " << moves.size() << std::endl;
            std::cout << "States Generated: " << pq.size() << std::endl;

            return moves;
        }
        /*
         *
         */
        // mark current state as visited
        visited.insert(*current);
        // generate children states
        for (state& child : getChildren(*current)) {
            // skip if this child has already been visited
            if (visited.count(child)) continue;

            // compute cost and heuristic
            child.g = current->g + 1;
            child.h = heuristic(child, goal);
            child.f = child.g + child.h;

            // set parent pointer and add to open list
            state* childPtr = new state(child);
            childPtr->parent = current;
            pq.push(childPtr);
        }
    }
    return {}; // no solution
}

// find the position of the 0
coord findZero(const state& s) {
    for (int y = 0; y < s.boardSize; ++y) {
        for (int x = 0; x < s.boardSize; ++x) {
            if (s.board[y][x] == 0) {
                return {y, x};
            }
        }
    }
    return {-1, -1};
}
