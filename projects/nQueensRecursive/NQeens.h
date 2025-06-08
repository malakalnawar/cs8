//
// Created by Elijah Ghossein on 3/26/25.
//

#ifndef NQUEENS_H
#define NQUEENS_H

#include <vector>

void write(const std::vector<int>& arr);
bool place(int row, int j, const std::vector<int> &arr);
void solveNQueens(int row, int &sol, std::vector<int> &arr);
std::vector<int> initializeBoard(int n);


#endif //NQUEENS_H
