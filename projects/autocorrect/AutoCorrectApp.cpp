//
// Created by Elijah Ghossein on 5/10/25.
//

#include "AutoCorrectApp.h"

AutoCorrectApp::AutoCorrectApp()
    : Application(720, 720, 32, "AutoCorrect"),
    autocorrect("/Users/elijahghossein/Documents/GitHub/cs8-new/projects/autocorrect/5000-baby-girl-names.txt", &textBox)
{

}

void AutoCorrectApp::initialization() {

    // set position of text box
    textBox.setPosition({360, 360});

    // add components
    addComponent(textBox);
    addComponent(textBox.cursor);
    addComponent(textBox.typer);
    addComponent(autocorrect);
    autocorrect.reposition();
    for (int i = 0; i < autocorrect.suggestions.size(); i++) {
        addComponent(autocorrect.suggestions[i]);
    }

}

void AutoCorrectApp::registerEvents() {

    textBox.typer.onKeypress([this]() {
        autocorrect.autocorrect();
    });

}
