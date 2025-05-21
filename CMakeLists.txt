cmake_minimum_required(VERSION 3.14)
project(cs8-new)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        malena
        GIT_REPOSITORY https://github.com/daversmith/Malena.git
        GIT_TAG v0.2.5
)
FetchContent_MakeAvailable(malena)

add_executable(cs8-new
        src/main.cpp
        ds/Heap.cpp
        ds/Heap.h
        projects/minesweeper/Node.cpp
        projects/minesweeper/Node.h
        projects/minesweeper/Model.cpp
        projects/minesweeper/Model.h
        projects/minesweeper/MinesweeperApp.cpp
        projects/minesweeper/MinesweeperApp.h
        projects/minesweeper/Backtracker.cpp
        projects/minesweeper/Backtracker.h
        algorithms/MergeSort.cpp
        algorithms/MergeSort.h
        algorithms/QuickSort.cpp
        algorithms/QuickSort.h
        algorithms/Dijkstra.cpp
        algorithms/Dijkstra.h
        ds/WeightedGraph.cpp
        ds/WeightedGraph.h
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
        ds/StateMachine.cpp
        ds/StateMachine.h
        ds/SMNode.cpp
        ds/SMNode.h
)

target_link_libraries(cs8-new PRIVATE Malena::Malena)
