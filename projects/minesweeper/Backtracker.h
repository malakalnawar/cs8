//
// Created by Elijah Ghossein on 5/4/25.
//

#ifndef BACKTRACKER_H
#define BACKTRACKER_H
#include <Malena/Graphics/Rectangle.h>
#include <Malena/Graphics/RectangleButton.h>

#include "Model.h"



class Backtracker {

    // bool solveIt(int nodeIndex);
    // void updateNeighbors();
    // bool validate();

    Model* board = nullptr;
    void setModel(Model* model);
    bool recursiveSolve(Model::NodesToCheckIterator it, Model* m);
    bool validate(Model* m) const;
    bool isSolved(Model* m) const;




public:

    bool solving = false;

    ml::RectangleButton flagButton;
    ml::Rectangle current;

    Backtracker(Model* board);

    void initialize(const sf::Font& font);
    bool solve();
    void takeAStep();





};



#endif //BACKTRACKER_H
