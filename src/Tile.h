//
// Created by Rohun Gargya on 12/4/2023.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

// Include necessary headers for SFML graphics library and array.
#include <SFML/Graphics.hpp>
#include <array>

// Using declarations to avoid prefixing with "sf::" and "std::".
using namespace std;
using namespace sf;

// Declaration of the Tile class.
class Tile {
public:
    // Enumeration to represent the possible states of a tile.
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };

    // Constructor for the Tile class, taking the initial position.
    Tile(Vector2f _position);

    // Getter method to retrieve the location (position) of the tile.
    Vector2f getLocation();

    // Getter method to retrieve the state of the tile.
    State getState();

    // Getter method to retrieve the array of neighbors for the tile.
    array<Tile*, 8>& getNeighbors();

    // Setter method to set the state of the tile.
    void setState(State _state);

    // Setter method to set the array of neighbors for the tile.
    void setNeighbors(array<Tile*, 8> _neighbors);

    // Method to handle left-click event on the tile.
    void onClickLeft();

    // Method to handle right-click event on the tile.
    void onClickRight();

    // Method to draw the tile.
    void draw();

protected:
    // Method to reveal the neighbors of the tile.
    void revealNeighbors();

private:
    // Declare friends (classes that can access private members) of the Tile class.
    friend class GameState;
    friend class Toolbox;

    // Private member variables for the Tile class.
    Vector2f position;           // Position of the tile.
    State state;                 // Current state of the tile.
    array<Tile*, 8> neighbors;   // Array of pointers to neighboring tiles.
    bool containsMine;           // Flag indicating whether the tile contains a mine.
    int number;                  // Number of mines in the neighboring tiles.

    // Private method to draw the tile with a specified sprite.
    void drawTile(const string& spriteKey, const Transform& transform);

    // Private method to draw the tile with a specified number.
    void drawTileWithNumber(int number, const Transform& transform);

};


#endif //MINESWEEPER_TILE_H
