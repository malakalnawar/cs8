cmake_minimum_required(VERSION 3.14)
project(cs8-new)

include(FetchContent)
FetchContent_Declare(
        malena
        GIT_REPOSITORY https://github.com/daversmith/Malena.git
        GIT_TAG v0.2.4
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
)

target_link_libraries(cs8-new PRIVATE Malena::Malena)
