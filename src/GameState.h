//
// Created by Rohun Gargya on 12/4/2023.
//

#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace std;
using namespace sf;

class GameState {
public:
    // Enumeration representing the possible play statuses of the game
    enum PlayStatus { WIN, LOSS, PLAYING };

    // Constructors for creating a new game state with default or custom dimensions and mine count
    GameState(Vector2i _dimensions = Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);

    // Getter methods for retrieving information about the game state
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();

    // Setter method for updating the play status
    void setPlayStatus(PlayStatus _status);

private:
    // Allow Toolbox class to access private members
    friend class Toolbox;

    // Private members representing the state of the game
    int totalMines;
    PlayStatus status;
    vector<vector<Tile>> board;
    Vector2i dimensions;
    int numOfFlags;
    int mineCount;

};


#endif //MINESWEEPER_GAMESTATE_H
