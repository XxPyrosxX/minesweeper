//
// Created by Rohun Gargya on 12/4/2023.
//
#include <iostream>
#include "fstream"
#include "GameState.h"

// Constructor for creating a new game state with default or custom dimensions and mine count
GameState::GameState(Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;

    // Create a 2D vector to represent the position of each Tile in the game
    vector<vector<Tile>> positionBoard(dimensions.y, vector<Tile>(dimensions.x, Tile(Vector2f(0, 0))));

    // Initialize each Tile and assign its position
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            positionBoard[i][j] = Tile(Vector2f(j, i));
        }
    }

    numOfFlags = 0;
    mineCount = 0;
    status = PLAYING;
    totalMines = _numberOfMines;

    // Randomly place mines on the board
    for (int i = 0; i < totalMines; i++) {
        int x = rand() % dimensions.x;
        int y = rand() % dimensions.y;

        // If the Tile already contains a mine, try placing it again
        if (positionBoard[y][x].containsMine) {
            i--;
        } else {
            positionBoard[y][x].containsMine = true;
        }
    }
    board = positionBoard;

    // Set neighbors for each Tile on the board
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            array<Tile*, 8> neighbors;
            for (int k = 0; k < 8; k++) {
                int ni = i + (k == 1 || k == 4 || k == 6 ? 0 : (k == 0 || k == 2 || k == 7 ? -1 : 1));
                int nj = j + (k == 3 || k == 0 || k == 5 ? 0 : (k == 1 || k == 2 || k == 6 ? -1 : 1));

                if (ni >= 0 && ni < board.size() && nj >= 0 && nj < board[0].size()) {
                    neighbors[k] = &board[ni][nj];
                } else {
                    neighbors[k] = nullptr;
                }
            }
            board[i][j].setNeighbors(neighbors);
        }
    }

    // Calculate and set the number of mines adjacent to each non-mine Tile
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (!board[i][j].containsMine) {
                for (Tile* neighbor : board[i][j].neighbors) {
                    if (neighbor != nullptr && neighbor->containsMine) {
                        board[i][j].number++;
                    }
                }
            }
        }
    }
    mineCount = totalMines;
}

// Constructor for creating a game state from a file with predefined mine positions
GameState::GameState(const char* filepath){
    ifstream file(filepath);
    vector<vector<int>> creatingBoard;
    string line;

    // Read the file and create a 2D vector to represent the mine positions
    while (getline(file, line)) {
        if (!line.empty()) {
            vector<int> row;
            for (char c : line) {
                row.push_back(c - '0');
            }
            creatingBoard.push_back(row);
        }
    }

    dimensions = Vector2i(creatingBoard[0].size(), creatingBoard.size());

    // Create a 2D vector to represent the position of each Tile in the game
    vector<vector<Tile>> positionBoard(dimensions.y, vector<Tile>(dimensions.x, Tile(Vector2f(0, 0))));

    // Initialize each Tile and assign its position
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            positionBoard[i][j] = Tile(Vector2f(j, i));
        }
    }

    numOfFlags = 0;
    mineCount = 0;
    status = PLAYING;
    totalMines = 0;

    // Place mines based on the predefined mine positions from the file
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            if (creatingBoard[i][j] == 1)
            {
                positionBoard[i][j].containsMine = true;
                totalMines += 1;
            }
        }
    }
    board = positionBoard;

    // Set neighbors for each Tile on the board
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            array<Tile*, 8> neighbors{};
            for (int k = 0; k < 8; k++) {
                int ni = i + (k == 1 || k == 4 || k == 6 ? 0 : (k == 0 || k == 2 || k == 7 ? -1 : 1));
                int nj = j + (k == 3 || k == 0 || k == 5 ? 0 : (k == 1 || k == 2 || k == 6 ? -1 : 1));

                if (ni >= 0 && ni < dimensions.y && nj >= 0 && nj < dimensions.x) {
                    neighbors[k] = &board[ni][nj];
                } else {
                    neighbors[k] = nullptr;
                }
            }
            board[i][j].setNeighbors(neighbors);
        }
    }

    // Calculate and set the number of mines adjacent to each non-mine Tile
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            if (!board[i][j].containsMine) {
                for (Tile* neighbor : board[i][j].neighbors) {
                    if (neighbor != nullptr && neighbor->containsMine) {
                        board[i][j].number++;
                    }
                }
            }
        }
    }

    mineCount = totalMines;
}

// Function to retrieve a pointer to the Tile at the specified coordinates
Tile* GameState::getTile(int x, int y) {
    return &board[y][x];
}

// Function to get the number of flagged Tiles
int GameState::getFlagCount() {
    return numOfFlags;
}

// Function to get the total number of mines in the game
int GameState::getMineCount() {
    return mineCount;
}

// Function to get the current play status of the game (WIN, LOSS, or PLAYING)
GameState::PlayStatus GameState::getPlayStatus() {
    return status;
}

// Function to set the play status of the game
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    status = _status;
}