//
// Created by Elijah Ghossein on 5/1/25.
//

#include "Model.h"
#include <cstdlib>
#include <ctime>
#include <Malena/Graphics/Text.h>

// constructor for model class
Model::Model(int cols, int rows, int bombs)
    : cols(cols), rows(rows), bombs(bombs)
{
    generateBoard(); // fill board with cols x rows nodes
    setBoard(); // set position of all nodes
    plantBombs(); // randomly place bombs on the board
    initializeNodes(); // calculate and assign surroundings for each node
}

void Model::setFont(const sf::Font &f) {
    // loserText.setFont(ml::FontManager::getFont("sfc"));
    loserText.setCharacterSize(30);
    loserText.setOutlineThickness(2.f);
    loserText.setOutlineColor(sf::Color(0,0,0,75));
    loserText.setFillColor(sf::Color(255, 104, 107));
    loserText.setString("You lose!");

    sf::Vector2f p = getBoardPos();
    sf::Vector2f s = getBoardSize();

    loserText.setPosition({
        p.x + s.x / 2 - (loserText.getGlobalBounds().size.x / 2),
        p.y + s.y / 2 - (loserText.getGlobalBounds().size.y / 2),
    });

    loserText.setState(ml::Stateful::HIDDEN, true);
}

// reveal and expansion
void Model::pressNode(coordinates pos, const std::vector<sf::Texture *> &textures) {
    if (!inBounds(pos.x, pos.y)) return;
    Node& node = board[pos.y][pos.x];
    if (node.isPressed()) return;
    node.press(textures);

    int nodeVal = node.getVal();

    if (nodeVal == 0) {
        for (auto n : node.getSurroundings()) {
            pressNode(n, textures);
        }
    }

    if (nodeVal > 0 && nodeVal < 9) {
        nodesToCheck.insert(pos);
    }

    if (nodeVal == 11) {
        youLose(pos);
    }
}

void Model::youLose(coordinates& pos) {

    for (auto& c : bombCoordinates) {
        getNode(c.x, c.y).press(textures);
    }

    loserText.setState(ml::Stateful::HIDDEN, false);

}

// updates open surroundings and generates combinations for each number node
void Model::updateNodeCombinations() {
    // update surroundings
    for (auto nodePos : nodesToCheck) {
        Node& node = getNode(nodePos.x, nodePos.y);
        std::vector<coordinates> surroundings = node.getSurroundings();
        std::vector<coordinates> open;
        for (auto sNodePos : surroundings) {
            Node& sNode = getNode(sNodePos.x, sNodePos.y);
            if (!sNode.isPressed()) {
                open.push_back(sNodePos);
            }
        }
        node.setOpenSurroundings(open);
    }
    // update combinations
    for (auto nodePos : nodesToCheck) {
        Node& node = getNode(nodePos.x, nodePos.y);
        int flagCount = node.getVal();
        std::vector<std::vector<coordinates>> combinations;
        std::vector<coordinates> combination;
        std::vector<coordinates> openSurroundings = node.getOpenSurroundings();

        generateCombinations(0, flagCount, combinations, combination, openSurroundings);
        node.setCombinations(combinations);
    }
}

// safely get a node from the board
Node& Model::getNode(int x, int y) {
    if (inBounds(x, y)) {
        return board[y][x];
    }
    throw std::out_of_range("retrieving a node out of bounds");
}

// print nodes that have number values and need checking
void Model::printNodesToCheck() const {
    std::cout << "nodes to check (" << nodesToCheck.size() << " total):\n";
    for (const auto& coord : nodesToCheck) {
        std::cout << "(" << coord.x << ", " << coord.y << ")\n";
    }
}

// recursively generate combinations of coordinates for flag placement
void Model::generateCombinations(
    int start,
    const int flagCount,
    std::vector<std::vector<coordinates>> &combinations,
    std::vector<coordinates> &combination,
    std::vector<coordinates> &openSurroundings
) {
    if (combination.size() == flagCount) {
        combinations.push_back(combination);
        return;
    }
    for (int i = start; i < openSurroundings.size(); ++i) {
        combination.push_back(openSurroundings[i]);
        generateCombinations(i + 1, flagCount, combinations, combination, openSurroundings);
        combination.pop_back();
    }
}

// generate empty board filled with default nodes
void Model::generateBoard() {
    for (int y = 0; y < rows; y++) {
        std::vector<Node> row;
        for (int x = 0; x < cols; x++) {
            Node node({x, y}, 0, false);
            row.push_back(node);
        }
        board.push_back(row);
    }
}

// assign screen position to each node
void Model::setBoard() {
    for (auto & node : *this) {
        coordinates pos = node.getPos();

        node.setSize({nodeSize, nodeSize});

        node.setPosition({
            boardPos + static_cast<float>(pos.x) * nodeSize,
            boardPos + static_cast<float>(pos.y) * nodeSize
        });

    }
}

sf::Vector2f Model::getNodePos(int x, int y) const {
    return { boardPos + static_cast<float>(x) * nodeSize, boardPos + static_cast<float>(y) * nodeSize };
}

// randomly plant bombs and increment surrounding node values
void Model::plantBombs() {
    srand(time(nullptr));
    int placed = 0;
    while (placed < bombs) {
        int x = rand() % cols;
        int y = rand() % rows;
        if (!board[y][x].isBomb()) {
            board[y][x].plantBomb();
            coordinates p = {x, y};
            bombCoordinates.push_back(p);
            placed++;
        }
    }

    for (auto bombCoordinate : bombCoordinates) {
        for (auto nodeCoordinate : nav) {
            int nx = bombCoordinate.x + nodeCoordinate.x;
            int ny = bombCoordinate.y + nodeCoordinate.y;
            if (inBounds(nx, ny)) {
                board[ny][nx].addOne();
            }
        }
    }
}

// initialize each node's list of surrounding coordinates
void Model::initializeNodes() {
    for (auto & node : *this) {
        coordinates pos = node.getPos();
        std::vector<coordinates> surroundings;
        for (auto nodeCoordinate : nav) {
            int nx = pos.x + nodeCoordinate.x;
            int ny = pos.y + nodeCoordinate.y;
            if (inBounds(nx, ny)) {
                surroundings.push_back({nx, ny});
            }
        }
        node.setSurroundings(surroundings);
    }
}

// check if given coordinates are within board bounds
bool Model::inBounds(int x, int y) const {
    return !(x < 0 || x >= board[0].size() || y < 0 || y >= board.size());
}

sf::Vector2f Model::getBoardPos() const {
    return {boardPos, boardPos};
}

sf::Vector2f Model::getBoardSize() const {
    float height = rows * nodeSize;
    float width = cols * nodeSize;
    return {width, height};
}

bool Model::canPlaceFlags(Node& node, const std::vector<coordinates> &combination) {
    int existingFlags = 0;
    for (auto c : node.getSurroundings()) {
        if (getNode(c.x, c.y).isFlagged()) {
            existingFlags++;
        }
    }

    int newFlags = 0;
    for (auto c : combination) {
        if (!getNode(c.x, c.y).isFlagged()) {
            newFlags++;
        }
    }

    int totalFlags = existingFlags + newFlags;
    return totalFlags <= node.getVal();
}

void Model::placeFlags(const std::vector<coordinates> &combination) {
    for (auto c : combination) {
        Node& node = getNode(c.x,c.y);
        node.flag(textures);
        flaggedNodes.insert(c);
    }
}

void Model::removeFlags(const std::vector<coordinates> &combination) {
    for (auto c : combination) {
        Node& node = getNode(c.x,c.y);
        node.unflag(textures);
        flaggedNodes.erase(c);
    }
}

void Model::removeAllFlags() {
    for (auto c : flaggedNodes) {
        Node& node = getNode(c.x,c.y);
        node.unflag(textures);
    }
    flaggedNodes.clear();
}

void Model::flagNode(int x, int y) {
    Node& node = getNode(x,y);
    node.flag(textures);
    flaggedNodes.insert({x, y});
}

void Model::unflagNode(int x, int y) {
    Node& node = getNode(x,y);
    node.unflag(textures);
    flaggedNodes.erase({x, y});
}

void Model::toggleNodeFlag(int x, int y) {
    Node& node = getNode(x,y);
    if (node.isFlagged()) {
        unflagNode(x, y);
    } else {
        flagNode(x, y);
    }
}

void Model::setTextures(const std::vector<sf::Texture *> &t) {
    textures = t;
}

void Model::logStep(const coordinates &node, const std::vector<coordinates> &flags, bool isPlacement) {
    steps.push_back({node, flags, isPlacement});
}

void Model::undoLastStep() {
    if (!steps.empty()) {
        steps.pop_back();
    }
}

void Model::clearSteps() {
    steps.clear();
}

std::deque<step>& Model::getSteps() {
    return steps;
}

void Model::printSteps() const {
    std::cout << "steps (" << steps.size() << " total):\n";
    for (const auto& s : steps) {
        std::cout << "node: (" << s.nodePosition.x << ", " << s.nodePosition.y << ") ";
        std::cout << (s.isPlacement ? "[placing] " : "[removing] ");
        std::cout << "flags: ";
        for (const auto& f : s.surroundingFlags) {
            std::cout << "(" << f.x << ", " << f.y << ") ";
        }
        std::cout << "\n";
    }
}

Model* Model::clone() const {
    Model* copy = new Model(*this); // invokes the copy constructor
    return copy;
}
