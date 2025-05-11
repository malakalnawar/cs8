//
// Created by Elijah Ghossein on 5/10/25.
//

#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <Malena/Graphics/Cursor.h>
#include <Malena/Graphics/Rectangle.h>
#include <Malena/Graphics/Typer.h>


class TextBox : public ml::Rectangle {

public:

    ml::Typer typer;
    ml::Cursor cursor;

    TextBox();

    void setPosition(const sf::Vector2f &position) override;
};



#endif //TEXTBOX_H
