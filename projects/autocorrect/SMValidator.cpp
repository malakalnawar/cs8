//
// Created by Elijah Ghossein on 5/20/25.
//

#include "SMValidator.h"

SMValidator::SMValidator(const std::string &filename, TextBox *textBox)
    : reader(filename), textBox(textBox)
{

}

bool SMValidator::isReservedKeywords(const std::string &input) {
    for (Word& w : reader.getWords()) {
        const std::string& word = w.getString();
        if (input == word) {
            return true;
        }
    }
    return false;
}

bool SMValidator::isValidIdentifier() {

    const std::string query = textBox->typer.getString();

    if (FSM.valid(query)) {
        if (!isReservedKeywords(query)) {
            return true;
        }
    }
    return false;

}


