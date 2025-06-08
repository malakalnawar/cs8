cmake_minimum_required(VERSION 3.14)
project(cs8)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


include(FetchContent)
FetchContent_Declare(
        malena
        GIT_REPOSITORY https://github.com/daversmith/Malena.git
        GIT_TAG v0.2.5
)
FetchContent_MakeAvailable(malena)

add_executable(cs8
        src/main.cpp
        algorithms/MergeSort.cpp
        algorithms/MergeSort.h
        algorithms/QuickSort.cpp
        algorithms/QuickSort.h
        algorithms/Dijkstra.cpp
        algorithms/Dijkstra.h
        algorithms/AStar.cpp
        algorithms/AStar.h
        ds/WeightedGraph.cpp
        ds/WeightedGraph.h
        ds/StateMachine.cpp
        ds/StateMachine.h
        ds/SMNode.cpp
        ds/SMNode.h
        ds/Heap.cpp
        ds/Heap.h
        ds/AVLTree.h
        ds/AVLTree.tpp
        ds/BSTree.h
        ds/BSTree.tpp
        ds/LinkedList.h
        ds/LinkedList.tpp
        ds/Node.h
        ds/NodeIterator.h
        ds/NodeIterator.tpp
        ds/R_NodeIterator.h
        ds/R_NodeIterator.tpp
        ds/TreeNode.h
        projects/autocorrect/AutoCorrectApp.cpp
        projects/autocorrect/AutoCorrectApp.h
        projects/autocorrect/TextBox.cpp
        projects/autocorrect/TextBox.h
        projects/autocorrect/Word.cpp
        projects/autocorrect/Word.h
        projects/autocorrect/FileReader.cpp
        projects/autocorrect/FileReader.h
        projects/autocorrect/WordSort.cpp
        projects/autocorrect/WordSort.h
        projects/autocorrect/SMValidator.cpp
        projects/autocorrect/SMValidator.h
        projects/slidingPuzzle/slidingPuzzleApp.cpp
        projects/slidingPuzzle/slidingPuzzleApp.h
        projects/slidingPuzzle/Board.cpp
        projects/slidingPuzzle/Board.h
        projects/slidingPuzzle/Tile.cpp
        projects/slidingPuzzle/Tile.h
        projects/slidingPuzzle/BoardController.cpp
        projects/slidingPuzzle/BoardController.h
        projects/minesweeper/Node.cpp
        projects/minesweeper/Node.h
        projects/minesweeper/Model.cpp
        projects/minesweeper/Model.h
        projects/minesweeper/MinesweeperApp.cpp
        projects/minesweeper/MinesweeperApp.h
        projects/minesweeper/Backtracker.cpp
        projects/minesweeper/Backtracker.h
        projects/gameLauncher/GameLauncher.cpp
        projects/gameLauncher/GameLauncher.h
        projects/nQueensRecursive/NQeens.h
        projects/nQueensRecursive/NQeens.cpp
)

target_link_libraries(cs8 PRIVATE Malena::Malena)
