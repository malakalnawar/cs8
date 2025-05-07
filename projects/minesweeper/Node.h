//
// Created by Elijah Ghossein on 5/1/25.
//

#ifndef NODE_H
#define NODE_H
#include <vector>
#include <Malena/Graphics/Rectangle.h>

struct coordinates {
    int x, y; // x = left-right, y = top-down

    coordinates operator+(const coordinates &other) const {
        return {x+other.x, y+other.y};
    }
    coordinates operator-(const coordinates &other) const {
        return {x-other.x, y-other.y};
    }
    // for sets
    bool operator<(const coordinates& other) const {
        return (y < other.y) || (y == other.y && x < other.x);
    }
};

class Node : public ml::Rectangle {

    coordinates pos; // node position (x = left-right, y = top-down)
    bool bomb; // true if node has a bomb
    bool pressed = false; // true if node has been revealed
    bool flagged = false; // true if node has been flagged
    int val; // number of surrounding bombs



    std::vector<coordinates> surroundings; // all surrounding node positions (relative to screen)
    std::vector<coordinates> openSurroundings; // unpressed surrounding nodes
    std::vector<std::vector<coordinates>> combinations; // possible flag placements (each is a list of coords)

public:

    Node(coordinates pos, int val, bool bomb); // constructor

    // getters
    [[nodiscard]] int getVal() const; // get value
    [[nodiscard]] coordinates getPos() const; // get position
    bool isBomb() const; // check if bomb
    bool isPressed() const; // check if pressed
    bool isFlagged() const; // check if flagged
    std::vector<coordinates> getSurroundings() const; // get all surroundings
    std::vector<coordinates> getOpenSurroundings() const; // get open surroundings

    // setters
    void setOpenSurroundings(const std::vector<coordinates>& list); // set open surroundings
    void setSurroundings(const std::vector<coordinates>& list); // set all surroundings
    void setCombinations(const std::vector<std::vector<coordinates>>& list); // set combinations

    void press(const std::vector<sf::Texture*> &textures); // reveal node
    void flag(const std::vector<sf::Texture*> &textures); // flag node
    void unflag(const std::vector<sf::Texture*> &textures); // un-flag node
    void toggleFlag(const std::vector<sf::Texture*> &textures); // toggle flag
    void addOne(); // increment value
    void plantBomb(); // make this node a bomb

    void printCombinations(); // print flag combinations
    void printSurroundings(); // print surrounding nodes

    // iterator for combinations
    class Iterator {
        std::vector<coordinates>* it;
    public:
        Iterator(std::vector<coordinates>* start) : it(start) {}

        std::vector<coordinates>& operator*() {
            return *it;
        }
        Iterator& operator++() {
            ++it;
            return *this;
        }
        Iterator& operator--() {
            --it;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }
        bool operator==(const Iterator& other) const {
            return it == other.it;
        }
    };

    Iterator begin() {
        return {&combinations[0]};
    }
    Iterator end() {
        return {&combinations[0] + combinations.size()};
    }
};



#endif //NODE_H
