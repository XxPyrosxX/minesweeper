//
// Created by Rohun Gargya on 12/4/2023.
//

#include "Button.h"

// Constructor for the Button class.
// Takes the position of the button and a function to be called on click.
Button::Button(Vector2f _position, function<void(void)> _onClick)
        : position(_position), onClickCallback(_onClick), sprite(nullptr) {}

// Getter method to retrieve the position of the button.
Vector2f Button::getPosition() {
    return position;
}

// Getter method to retrieve the sprite associated with the button.
Sprite* Button::getSprite() {
    return sprite;
}

// Setter method to set the sprite associated with the button.
void Button::setSprite(Sprite* _sprite) {
    sprite = _sprite;
}

// Method to trigger the onClick callback function.
void Button::onClick() {
    onClickCallback();
}