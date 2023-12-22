# Minesweeper
## Overview

This project is designed to provide students with practice building and working within an object-oriented paradigm by constructing classes to represent the elements of the classic PC game "Minesweeper" and implementing a working version.

## Gameplay

Minesweeper is a classic game where the goal is to reveal all tiles that are free of mines on a grid. Key gameplay elements include:

    Left-click on a tile to reveal it.
    Right-click on a tile to flag it as a possible mine.
    If a mine is revealed, the player loses. If all non-mine tiles are revealed, the player wins.
    Tiles indicate the number of adjacent mines (1-8), or empty for 0.
    Flagged spaces cannot be revealed, but right-clicking again removes the flag.

## Mine Counter

A counter tracks the number of mines remaining. It decreases when a flag is placed and increases when a flag is removed.

## Buttons

The game includes buttons for various functionalities:

    New Game: Restarts the game, randomly reassigning mines.
    Debug Mines: Toggles visibility of mines on the board for testing/debugging.
    Test Buttons: Load predefined test boards for specific configurations.

## Structure

The project structure includes important elements such as window management, event management, and images. The SFML window must be 800x600 with specific title text. Events are processed through polling and filtering.

## Images

All required images are in the "images" folder. These include game images and UI images necessary for button visualization.

## Board Files

Pre-generated game boards can be loaded from board files (brd) stored as plain text. The README provides an example of a board file format.

## Requirements

    I used SFML v2.5.1 for this project.
    Construction of several classes and functions, with all attributes/methods private unless noted.
    Key classes include Toolbox, Button, Tile, and GameState.

## Global Functions

Global functions include launch(), restart(), render(), toggleDebugMode(), and getDebugMode(). These functions encapsulate game logic and UI rendering.

## How to Run

The main() function is defined as follows:
int main() { return launch(); }
This invokes the launch() function, initiating the Minesweeper game.

