//
// Created by Rohun Gargya on 12/4/2023.
//

#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include "SFML/Graphics.hpp"

// Using directives to avoid prefixing SFML classes with sf:: and std::
using namespace std;
using namespace sf;

int launch(); // Function to launch the Minesweeper game
void restart(); // Function to restart the Minesweeper game
void render(); // Function to render the Minesweeper game
void toggleDebugMode(); // Function to toggle the debug mode in the Minesweeper game
bool getDebugMode(); // Function to get the current state of the debug mode in the Minesweeper game
int gameLoop(); // Function representing the main game loop for Minesweeper

#endif //MINESWEEPER_MINESWEEPER_H
