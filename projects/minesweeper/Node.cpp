//
// Created by Elijah Ghossein on 5/1/25.
//

#include "Node.h"
#include <iostream>

// constructor
Node::Node(coordinates pos, int val, bool bomb)
    : pos(pos), val(val), bomb(bomb) {

}

// get value
int Node::getVal() const {
    return val;
}

// get position
coordinates Node::getPos() const {
    return pos;
}

// check if bomb
bool Node::isBomb() const {
    return bomb;
}

// check if pressed
bool Node::isPressed() const {
    return pressed;
}

bool Node::isFlagged() const {
    return flagged;
}

// get all surroundings
std::vector<coordinates> Node::getSurroundings() const {
    return surroundings;
}

// get open surroundings
std::vector<coordinates> Node::getOpenSurroundings() const {
    return openSurroundings;
}

// set open surroundings
void Node::setOpenSurroundings(const std::vector<coordinates> &list) {
    openSurroundings = list;
}

// set all surroundings
void Node::setSurroundings(const std::vector<coordinates> &list) {
    surroundings = list;
}

// set combinations
void Node::setCombinations(const std::vector<std::vector<coordinates>> &list) {
    combinations = list;
}

// reveal node
void Node::press(const std::vector<sf::Texture*> &textures) {
    if (!pressed) {
        setTexture(textures[val]);
        pressed = true;
    }
}

// flag node
void Node::flag(const std::vector<sf::Texture *> &textures) {
    setTexture(textures[9]);
    flagged = true;
}

// un-flag node
void Node::unflag(const std::vector<sf::Texture *> &textures) {
    setTexture(textures[12]);
    flagged = false;
}

void Node::toggleFlag(const std::vector<sf::Texture *> &textures) {
    if (!pressed) {
        if (!flagged) {
            flag(textures);
        } else {
            unflag(textures);
        }
    }
}

// increment value
void Node::addOne() {
    if (!bomb) {
        val++;
    }
}

// make this node a bomb
void Node::plantBomb() {
    bomb = true;
    val = 11;
}

// print flag combinations
void Node::printCombinations() {
    std::cout << "Node at (" << pos.x << ", " << pos.y << ") [x=left-right, y=top-down]:\n";
    for (const auto& combo : combinations) {
        std::cout << "  Combination:\n    ";
        for (const auto& coord : combo) {
            std::cout << "(" << coord.x << ", " << coord.y << ") ";
        }
        std::cout << "\n";
    }
}

// print surrounding nodes
void Node::printSurroundings() {
    std::cout << "Surroundings of node at (" << pos.x << ", " << pos.y << ") [x=left-right, y=top-down]:\n";
    for (const auto& coord : surroundings) {
        std::cout << "(" << coord.x << ", " << coord.y << ") ";
    }
    std::cout << "\n";
}
