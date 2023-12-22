//
// Created by Rohun Gargya on 12/4/2023.


#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H

// Include necessary headers for SFML graphics library and functional utilities.
#include <SFML/Graphics.hpp>
#include <functional>

// Using declarations to avoid prefixing with "sf::" and "std::".
using namespace sf;
using namespace std;

// Declaration of the Button class.
class Button {
public:
    // Constructor for the Button class.
    // Takes the position of the button and a function to be called on click.
    Button(Vector2f _position, function<void(void)> _onClick);

    // Getter method to retrieve the position of the button.
    Vector2f getPosition();

    // Getter method to retrieve the sprite associated with the button.
    Sprite* getSprite();

    // Setter method to set the sprite associated with the button.
    void setSprite(Sprite* _sprite);

    // Method to trigger the onClick callback function.
    void onClick();

private:
    // Private member variables for the Button class.
    Vector2f position;                     // Position of the button.
    function<void(void)> onClickCallback;  // Callback function to be executed on click.
    Sprite* sprite;                        // Pointer to the sprite associated with the button.
};


#endif //MINESWEEPER_BUTTON_H
