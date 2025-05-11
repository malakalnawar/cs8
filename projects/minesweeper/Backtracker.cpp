//
// Created by Elijah Ghossein on 5/4/25.
//

#include "Backtracker.h"
#include <Malena/Managers/FontManager.h>

Backtracker::Backtracker(Model* model) {
    setModel(model);
}

void Backtracker::setModel(Model *model) {
    this->board = model;
}

void Backtracker::initialize(const sf::Font &font) {
    // setup flag button
    sf::Vector2f bPos = board->getBoardPos();
    sf::Vector2f bSize = board->getBoardSize();
    flagButton.setSize({bSize.x, 50});
    flagButton.setPosition({
        bPos.x,
        bPos.y + bSize.y + 5.f,
    });
    flagButton.setFont(font);
    flagButton.setString("Flag");
    flagButton.setFillColor(sf::Color(255, 104, 107));
}

bool Backtracker::solve() {
    solving = true;

    // hide current
    current.setSize({0, 0});
    current.setPosition({0, 0});

    // remove flags and steps of previous solves
    board->removeAllFlags();
    board->clearSteps();

    // create a copy of the board
    const auto tempBoard = new Model(*board);
    Backtracker tempSolver(tempBoard);

    // run recursive solving on the copy
    bool solved = tempSolver.recursiveSolve(tempBoard->beginNodesToCheck(), tempBoard);

    // transfer steps from tempBoard to real board
    if (solved) {
        for (const auto& s : tempBoard->getSteps()) {
            board->logStep(s.nodePosition, s.surroundingFlags, s.isPlacement);
        }
    }

    delete tempBoard;
    solving = false;
    // board->printSteps();
    return solved;
}

bool Backtracker::recursiveSolve(Model::NodesToCheckIterator it, Model* m) {
    if (it == m->endNodesToCheck()) {
        return isSolved(m);
    }

    Node& node = *it;

    for (auto combIt = node.begin(); combIt != node.end(); ++combIt) {
        const std::vector<coordinates>& combination = *combIt;

        if (m->canPlaceFlags(node, combination)) {

            m->placeFlags(combination);
            m->logStep(node.getPos(), combination, true); // log step to place flags

            // if (validate(m)) {
                auto next = it;
                ++next;
                if (recursiveSolve(next, m)) return true;
            // }

            m->removeFlags(combination);
            m->logStep(node.getPos(), combination, false); // log step to remove flags
        }
    }

    return false;
}

void Backtracker::takeAStep() {

    std::deque<step>& steps = board->getSteps();

    if (!steps.empty() && !solving) {
        step s = steps.front();
        steps.pop_front();

        const Node& node = board->getNode(s.nodePosition.x, s.nodePosition.y);

        // board->removeFlags(node.getOpenSurroundings());
        if (s.isPlacement) {
            board->placeFlags(s.surroundingFlags);
        } else {
            board->removeFlags(s.surroundingFlags);
        }


        sf::Vector2f pos = node.getPosition();
        sf::Vector2f size = node.getSize();
        current.setSize({size.x, size.y});
        current.setPosition({pos.x, pos.y});
        current.setFillColor(sf::Color(255, 255, 0, 75));
    }

}

bool Backtracker::validate(Model* m) const {
    for (auto it = m->beginNodesToCheck(); it != m->endNodesToCheck(); ++it) {
        const Node& node = *it;
        const int val = node.getVal();
        int flagCount = 0;
        for (auto& c : node.getOpenSurroundings()) {
            if (m->getNode(c.x,c.y).isFlagged()) {
                flagCount++;
            }
        }
        if (flagCount > val) {
            return false;
        }
    }
    return true;
}

bool Backtracker::isSolved(Model* m) const {
    for (auto it = m->beginNodesToCheck(); it != m->endNodesToCheck(); ++it) {
        const Node& node = *it;
        const int expected = node.getVal();
        int actual = 0;
        for (auto& [x, y] : node.getSurroundings()) {
            if (m->getNode(x,y).isFlagged()) {
                actual++;
            }
        }
        if (actual != expected) return false;
    }
    return true;
}
