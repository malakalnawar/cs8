
#include "../projects/gameLauncher/GameLauncher.h"
#include "../projects/slidingPuzzle/slidingPuzzleApp.h"

int main() {

    GameLauncher app;
    app.run();

    return 0;
}

// test a 5x5 board
// std::vector<std::vector<int>> goal = {
//     {1, 2, 3, 4, 5},
//     {6, 7, 8, 9, 10},
//     {11, 12, 13, 14, 15},
//     {16, 17, 18, 19, 20},
//     {21, 22, 23, 24, 0}
// };
// std::vector<std::vector<int>> current = {
//     {2, 12, 8, 3, 5},
//     {1, 4, 0, 10, 15},
//     {6, 13, 17, 14, 20},
//     {11, 22, 7, 19, 9},
//     {16, 21, 18, 23, 24}
// };
// state s = state(current);
// state g = state(goal);
// std::cout << "Manhattan Distance:" << std::endl;
// const std::vector<int> path0 = aStar(s, g, manhattanDistance);
// std::cout << "Custom Heuristic:" << std::endl;
// const std::vector<int> path1 = aStar(s, g, customHeuristic);
//
// if (path0.empty()) {
//     std::cout << "No solution found." << std::endl;
// }
// if (path1.empty()) {
//     std::cout << "No solution found." << std::endl;
// }

