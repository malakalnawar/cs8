//
// Created by Elijah Ghossein on 5/1/25.
//

#ifndef TILE_H
#define TILE_H
#include <vector>
#include <Malena/Graphics/Rectangle.h>

struct coord {
    int y, x; // y = top-down, x = left-right

    coord operator+(const coord &other) const {
        return {y+other.y, x+other.x};
    }
    bool operator==(const coord& other) const {
        return y == other.y && x == other.x;
    }

};

class Tile : public ml::Rectangle {

    int val;
    coord pos;

public:

    coord getPos() const { return pos; }
    void setPos(const coord p) { pos = p; }
    int getVal() const { return val; }
    void setVal(int v) { val = v; }

    Tile(coord pos, int val); // constructor


};



#endif //TILE_H
