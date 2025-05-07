//
// Created by Elijah Ghossein on 5/1/25.
//

#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "Node.h"
#include <set>
#include "Malena/Graphics/Text.h"

struct step {
    coordinates nodePosition;
    std::vector<coordinates> surroundingFlags;
    bool isPlacement = true;
};

class Model {

    std::vector<std::vector<Node>> board; // game board of nodes, indexed as board[y][x]
    int cols; // number of columns
    int rows; // number of rows
    int bombs; // number of bombs to plant
    float boardPos = 40.f; // board screen position
    float nodeSize = 40.f; // node size

    std::vector<coordinates> bombCoordinates; // coordinates of planted bombs
    std::set<coordinates> nodesToCheck; // pressed number nodes
    std::set<coordinates> flaggedNodes; // coordinates of flagged nodes
    std::deque<step> steps;

    std::vector<sf::Texture*> textures; // container for all textures

    std::vector<coordinates> nav = { // directional offsets
        {0,-1},
        {-1,-1},
        {-1,0},
        {-1,1},
        {0,1},
        {1,1},
        {1,0},
        {1,-1}
    };

    void generateCombinations( // recursive combo builder
        int start,
        int flagCount,
        std::vector<std::vector<coordinates>> &combinations,
        std::vector<coordinates> &combination,
        std::vector<coordinates> &openSurroundings
    );

    void generateBoard(); // fill board with nodes
    void setBoard(); // set position and size of all nodes
    void plantBombs(); // place random nodes
    void initializeNodes(); // assign surroundings to each node
    void youLose(coordinates& pos);

    [[nodiscard]] bool inBounds(int x, int y) const; // return false if out of bounds

public:

    ml::Text loserText;

    Model(int cols, int rows, int bombs); // constructor

    int getNonBombCount() const {
        int total = cols * rows - bombs;
        return total;
    }


    void setFont(const sf::Font &f);
    void setTextures(const std::vector<sf::Texture*> &t);
    // bool isSolved();
    std::deque<step>& getSteps();
    void logStep(const coordinates& node, const std::vector<coordinates>& flags, bool isPlacement);
    void undoLastStep();
    void clearSteps();
    Model *clone() const;

    void pressNode(coordinates pos, const std::vector<sf::Texture*> &textures); // reveal logic
    void updateNodeCombinations(); // update combinations for each number node
    Node& getNode(int x, int y); // return node at (x=left-right, y=top-down)
    [[nodiscard]] sf::Vector2f getNodePos(int x, int y) const;
    [[nodiscard]] sf::Vector2f getBoardPos() const;
    [[nodiscard]] sf::Vector2f getBoardSize() const;

    bool canPlaceFlags(Node& node, const std::vector<coordinates> &combination);
    void placeFlags(const std::vector<coordinates> &combination);
    void removeFlags(const std::vector<coordinates> &combination);
    void removeAllFlags();
    void flagNode(int x, int y);
    void unflagNode(int x, int y);
    void toggleNodeFlag(int x, int y);

    void printSteps() const;
    void printNodesToCheck() const; // print tracked number nodes

    /*
     * iterator for board
     */
    class Iterator {
        Model* model; // pointer to model
        int y; // vertical position (row)
        int x; // horizontal position (column)
    public:
        Iterator(Model* m, int row, int col) : model(m), y(row), x(col) {}

        Node& operator*() {
            return model->board[y][x];
        }
        Iterator& operator++() {
            if (++x >= model->board[y].size()) {
                x = 0;
                ++y;
            }
            return *this;
        }
        Iterator& operator--() {
            if (x == 0) {
                --y;
                x = model->board[y].size() - 1;
            } else {
                --x;
            }
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return y != other.y || x != other.x;
        }
        bool operator==(const Iterator& other) const {
            return y == other.y && x == other.x;
        }
    };
    Iterator begin() {
        return {this, 0, 0};
    }
    Iterator end() {
        return {this, static_cast<int>(board.size()), 0};
    }

    /*
     * iterator for nodesToCheck
     */
    class NodesToCheckIterator {
        Model* m;
        std::set<coordinates>::iterator it;
    public:
        NodesToCheckIterator(Model* model, std::set<coordinates>::iterator iterator) : m(model), it(iterator) {}

        Node& operator*() {
            coordinates pos = *it;
            return m->getNode(pos.x, pos.y); // x=left-right, y=top-down
        }
        NodesToCheckIterator& operator++() {
            ++it;
            return *this;
        }
        bool operator!=(const NodesToCheckIterator& other) const {
            return it != other.it;
        }
        bool operator==(const NodesToCheckIterator& other) const {
            return it == other.it;
        }
    };
    NodesToCheckIterator beginNodesToCheck() {
        return {this, nodesToCheck.begin()};
    }
    NodesToCheckIterator endNodesToCheck() {
        return {this, nodesToCheck.end()};
    }

};



#endif //MODEL_H
