//
// Created by Elijah Ghossein on 3/26/25.
//

#include "NQeens.h"

#include <iostream>

void write(const std::vector<int> &arr) {
    std::cout << "solution found: ";
    for (int i : arr) {
        std::cout << (i + 1) << " ";
    }
    std::cout << std::endl;
}

bool place(int row, int col, const std::vector<int> &arr) {
    for (int j = 0 ; j < row; j++) {
        if ((arr[j] == col) || (abs(arr[j] - col) == abs(j - row))) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int row, int &sol, std::vector<int> &arr) {
    for (int col = 0; col < arr.size(); col++) {
        if (place(row, col, arr)) {

            arr[row] = col;

            if (row == arr.size() - 1) {
                write(arr);
                sol++;
            } else {
                solveNQueens(row + 1, sol, arr);
            }
        }
    }
}

std::vector<int> initializeBoard(int n) {
    std::vector<int> arr(n, 0);
    std::cout << "Initial board configuration: ";
    for (int i : arr) { std::cout << i << " "; }
    std::cout << std::endl;
    return arr;
}
