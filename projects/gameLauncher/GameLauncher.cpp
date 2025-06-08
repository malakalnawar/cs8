//
// Created by Elijah Ghossein on 5/28/25.
//

#include "GameLauncher.h"

#include "../minesweeper/minesweeperApp.h"
#include "../slidingPuzzle/slidingPuzzleApp.h"


GameLauncher::GameLauncher() {



}

void GameLauncher::registerEvents() {

    textBox.onTextEntered([this]() {

        autocorrect.autocorrect();

        std::string query = textBox.typer.getString();

        if (validator.isValidIdentifier()) {
            textBox.typer.setFillColor({0,255,0});
        } else {
            textBox.typer.setFillColor({255,0,0});
        }

        if (query == "minesweeper\n") {
            query.pop_back();
            textBox.typer.setString(query);
            MinesweeperApp ms(8, 8, 10);
            ms.run();
        }
        if (query == "8-puzzle\n") {
            query.pop_back();
            // textBox.typer.setString(query);
            std::cout << query << std::endl;

            slidingPuzzleApp sp(false);
            sp.run();

         }
        if (query == "15-puzzle\n") {
            query.pop_back();

            slidingPuzzleApp sp(true);
            sp.run();

         }

    });
}
