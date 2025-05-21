//
// Created by Elijah Ghossein on 5/10/25.
//

#include "TextBox.h"

TextBox::TextBox() {

    // Initialize text box (rectangle)
    setSize({200, 40});
    setFillColor({0, 0, 0, 0});
    setOutlineThickness(5);
    setOutlineColor({255, 255, 255});

    // Initialize cursor
    cursor.disableState(BLINKING);
    cursor.enableState(HIDDEN);

    // Initialize typer
    typer.setCharacterSize(26);
    typer.setFillColor({255,255,255});



    // update cursor and typer postions automatically
    onUpdate([this] () {

        if (typer.getGlobalBounds().size.x > getGlobalBounds().size.x - 30.f) {
            std::string text = typer.getString();
            text.pop_back();
            typer.setString(text);
        }

        float x1 = TextBox::getGlobalBounds().position.x;
        float y1 = TextBox::getGlobalBounds().position.y;

        typer.setPosition({x1 + 6.f, y1 + 8.f});

        float x2 = x1 + typer.getGlobalBounds().size.x;

        cursor.setPosition({x2 + 6.f, y1 + 4.f});


    });

    onFocus([this] () {
        setOutlineColor({119,182,234});
        cursor.setFillColor({119,182,234});

        typer.enableState(ENABLED);

        cursor.enableState(BLINKING);
        cursor.disableState(HIDDEN);
    });

    onBlur([this] () {
        setOutlineColor({255, 255, 255});

        typer.disableState(ENABLED);

        cursor.disableState(BLINKING);
        cursor.enableState(HIDDEN);
    });

}

// coordinates are now text box center
void TextBox::setPosition(const sf::Vector2f &position) {

    const float x = position.x;
    const float y = position.y;

    const float xOffset = getGlobalBounds().size.x / 2;
    const float yOffset = getGlobalBounds().size.y / 2;

    Rectangle::setPosition({x - xOffset, y - yOffset});

}
