//
// Created by Elijah Ghossein on 5/26/25.
//

#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H
#include <Malena/Graphics/RectangleButton.h>

#include "Board.h"


class BoardController {

  Board* board;

  void setup();

  std::vector<std::vector<int>> goal;


public:

  ml::RectangleButton randomize;

  ml::RectangleButton solve;

  BoardController(Board* board, bool fifteen);
  void solveBoard();

};

#endif //BOARDCONTROLLER_H
