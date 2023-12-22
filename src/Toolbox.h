//
// Created by Rohun Gargya on 12/4/2023.
//

#ifndef MINESWEEPER_TOOLBOX_H
#define MINESWEEPER_TOOLBOX_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Tile.h"
#include "GameState.h"
#include <vector>
#include <functional>

// Using declarations for convenience
using namespace std;
using namespace sf;

// Toolbox class declaration
class Toolbox {
public:
    RenderWindow window; // SFML RenderWindow for graphical interface
    GameState* gameState; // Pointer to the current game state

    // Buttons for game interaction
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    Button* testButton3;

    // Static method to access a singleton instance of the Toolbox
    static Toolbox& getInstance();

    Vector2i dimensions;  // Dimensions of the game board in tiles
    map<string, Sprite*> allSprites;  // Map to store all loaded sprites

    // Functions representing different button click behaviors
    function<void(void)> clickButton1();
    function<void(void)> clickButton2();
    function<void(void)> clickButton3();
    function<void(void)> clickNewGame();
    function<void(void)> clickDebugMode();

    // Tile dimensions
    int tileHeight = 32;
    int tileWidth = 32;

    bool debugMode; // Flag indicating whether debug mode is active
    void mouseClick(Event event); // Event handler for mouse clicks
    RenderTexture boardSprite; // RenderTexture for the game board
    int minesLeft; // Count of mines left in the game
    string *minesLeftText; // Text displaying the number of mines left
    bool won(); // Function to check if the game is won

private:
    ~Toolbox(); // Destructor (private to enforce singleton)
    Toolbox(); // Private constructor to enforce singleton

    // Friend classes
    friend class GameState;
    friend class Tile;

    void drawMineTile(const Tile& tile, int x, int y); // Draw a mine tile at the specified position
    void initializeWindow(); // Initialize the SFML window
    void initializeSprites(); // Load all sprites required for the game
    void initializeGame(); // Initialize the game state and buttons

    // Create a button with specified properties
    Button* createButton(const Vector2f& position, const string& spriteKey, const function<void()>& onClick);

    void updateMinesLeftText();  // Update the text displaying the number of mines left
    void loadSprite(const string& filename, const string& key, bool rect, int i); // Load a sprite with optional texture rect
    void createNumberedSprite(int number); // Create a sprite for a numbered tile
    void createFlaggedMineSprites(); // Create sprites for flagged and mine tiles
};


#endif //MINESWEEPER_TOOLBOX_H
