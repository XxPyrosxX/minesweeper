//
// Created by Rohun Gargya on 12/4/2023.
//

// Include the header files for the Tile class and Toolbox.
#include "Tile.h"
#include "Toolbox.h"

// Constructor for the Tile class, initializing member variables.
Tile::Tile(Vector2f _position) : position(_position * 32.0f), state(HIDDEN), neighbors(), containsMine(false) {}

// Getter method to retrieve the location (position) of the tile.
Vector2f Tile::getLocation() {
    return position;
}

// Getter method to retrieve the state of the tile.
Tile::State Tile::getState() {
    return state;
}

// Getter method to retrieve the array of neighbors for the tile.
array<Tile*, 8>& Tile::getNeighbors() {
    return neighbors;
}

// Setter method to set the state of the tile.
void Tile::setState(State _state) {
    state = _state;
}

// Setter method to set the array of neighbors for the tile.
void Tile::setNeighbors(array<Tile*, 8> _neighbors) {
    neighbors = _neighbors;
}

// Method to handle left-click event on the tile.
void Tile::onClickLeft() {
    if (state == HIDDEN){
        state = REVEALED;
        revealNeighbors();
    }
}

// Method to handle right-click event on the tile.
void Tile::onClickRight() {
    if(state == FLAGGED) {
        state = HIDDEN;
    } else if (state == HIDDEN) {
        state = FLAGGED;
    }
}

// Method to reveal the neighbors of the tile.
void Tile::revealNeighbors() {
    for (int i = 0; i < 8; i++) {
        auto& currentNeighbor = neighbors[i];

        if (currentNeighbor != nullptr) {
            switch (currentNeighbor->getState()) {
                case HIDDEN:
                    if (!currentNeighbor->containsMine) {
                        if (currentNeighbor->number == 0) {
                            currentNeighbor->setState(REVEALED);
                            currentNeighbor->revealNeighbors();
                        } else {
                            currentNeighbor->setState(REVEALED);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

// Private method to draw the tile with a specified sprite.
void Tile::drawTile(const string& spriteKey, const Transform& transform) {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.boardSprite.draw(*toolbox.allSprites[spriteKey], transform);
}

// Private method to draw the tile with a specified number.
void Tile::drawTileWithNumber(int number, const Transform& transform) {
    string spriteKey = (number == 0) ? "tile_revealed.png" : "numbered_" + to_string(number);
    drawTile(spriteKey, transform);
}

// Method to draw the tile based on its state.
void Tile::draw(){
    switch (state) {
        case HIDDEN:
            if (containsMine && Toolbox::getInstance().debugMode) {
                drawTile("tile_mine", Transform().translate(position));
            } else {
                drawTile("tile_hidden.png", Transform().translate(position));
            }
            break;

        case REVEALED:
            drawTileWithNumber(number, Transform().translate(position));
            break;

        case FLAGGED:
            drawTile("tile_flagged", Transform().translate(position));
            break;

        case EXPLODED:
            drawTile("tile_mine", Transform().translate(position));
            break;
    }
}