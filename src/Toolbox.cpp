//
// Created by Rohun Gargya on 12/4/2023.
//

#include "Toolbox.h"
#include "memory"
#include <algorithm>

// Singleton pattern: returns a reference to the singleton instance of Toolbox
Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}

// Constructor for Toolbox: initializes the SFML window, loads sprites, and sets up the game
Toolbox::Toolbox(){
    initializeWindow();
    initializeSprites();
    initializeGame();
}

// Initializes the SFML window
void Toolbox::initializeWindow() {
    // Create SFML window
    window.create(VideoMode(800, 600), "Minesweeper - <Rohun Gargya>");
}

// Loads a sprite from file and adds it to the allSprites map
void Toolbox::loadSprite(const string& filename, const string& key, bool rect, int i) {
    Texture* texture = new Texture();
    if(rect) {
        // Load sprite with a texture rectangle (sub-image)
        texture->loadFromFile("../resources/images/" + filename, IntRect(i * 21, 0, 21, tileHeight));
    } else {
        // Load sprite without texture rectangle
        texture->loadFromFile("../resources/images/" + filename);
    }
    allSprites[key] = new Sprite(*texture);
}

// Creates a numbered sprite by combining the revealed tile and a numbered sprite
void Toolbox::createNumberedSprite(int number) {
    RenderTexture texture;
    texture.create(tileWidth, tileHeight);
    texture.draw(*allSprites["tile_revealed.png"]);
    texture.draw(*allSprites["number_" + to_string(number) + ".png"]);
    texture.display();
    Texture* texture2 = new Texture(texture.getTexture());
    texture2->loadFromImage(texture.getTexture().copyToImage());
    allSprites["numbered_" + to_string(number)] = new Sprite(*texture2);
}

// Creates sprites for flagged and mine tiles
void Toolbox::createFlaggedMineSprites() {
    // Flagged
    RenderTexture textureFlag;
    textureFlag.create(tileWidth, tileHeight);
    textureFlag.draw(*allSprites["tile_hidden.png"]);
    textureFlag.draw(*allSprites["flag.png"]);
    textureFlag.display();
    Texture tempFlag;
    tempFlag.loadFromImage(textureFlag.getTexture().copyToImage());
    Texture* allocatedTextureFlag = new Texture(tempFlag);
    allSprites["tile_flagged"] = new Sprite(*allocatedTextureFlag);

    // Mine
    RenderTexture textureMine;
    textureMine.create(tileWidth, tileHeight);
    textureMine.draw(*allSprites["tile_hidden.png"]);
    textureMine.draw(*allSprites["mine.png"]);
    textureMine.display();
    Texture tempMine;
    tempMine.loadFromImage(textureMine.getTexture().copyToImage());
    Texture* allocatedTextureMine = new Texture(tempMine);
    allSprites["tile_mine"] = new Sprite(*allocatedTextureMine);
}

// Initializes all sprites needed for the game
void Toolbox::initializeSprites() {
    string filenames[] = {
            "debug.png", "digits.png", "face_happy.png", "face_lose.png", "face_win.png",
            "flag.png", "mine.png", "number_1.png", "number_2.png", "number_3.png",
            "number_4.png", "number_5.png", "number_6.png", "number_7.png", "number_8.png",
            "test_1.png", "test_2.png", "Test_3.png", "tile_hidden.png", "tile_revealed.png"
    };

    for (const auto& filename : filenames) {
        loadSprite(filename, filename, false, 0);
    }

    for (int i = 0; i < 11; ++i) {
        loadSprite("digits.png", "digit_" + to_string(i), true, i);
    }

    for (int i = 1; i < 9; ++i) {
        createNumberedSprite(i);
    }

    createFlaggedMineSprites();
}

// Initializes the game state and buttons
void Toolbox::initializeGame() {
    gameState = new GameState();

    // Create a RenderTexture for the game board
    boardSprite.create(gameState->dimensions.x * tileWidth, gameState->dimensions.y * tileHeight);

    // Create buttons for game interaction
    Vector2f buttonPosition(0, gameState->dimensions.y * tileHeight);

    debugButton = createButton(buttonPosition, "debug.png", clickDebugMode());
    buttonPosition.x += tileWidth;

    testButton1 = createButton(buttonPosition, "test_1.png", clickButton1());
    buttonPosition.x += tileWidth;

    testButton2 = createButton(buttonPosition, "test_2.png", clickButton2());
    buttonPosition.x += tileWidth;

    testButton3 = createButton(buttonPosition, "Test_3.png", clickButton3());
    buttonPosition.x += tileWidth;

    newGameButton = createButton(buttonPosition, "tile_hidden.png", clickNewGame());

    // Initialize the game board with hidden tiles
    for (int i = 0; i < gameState->dimensions.x; ++i) {
        for (int j = 0; j < gameState->dimensions.y; ++j) {
            boardSprite.draw(*allSprites["tile_hidden.png"], Transform().translate(i * tileWidth, j * tileHeight));
        }
    }

    // Set the dimensions and display the game board
    dimensions = Vector2i(gameState->dimensions.x * tileWidth, gameState->dimensions.y * tileHeight);
    boardSprite.display();

    updateMinesLeftText();
}

// Create a button given a sprite, position
Button* Toolbox::createButton(const Vector2f& position, const string& spriteKey, const function<void()>& onClick) {
    Button* button = new Button(position, onClick);
    button->setSprite(allSprites[spriteKey]);
    return button;
}

// Update the Mines Left text
void Toolbox::updateMinesLeftText() {
    minesLeft = gameState->mineCount - gameState->numOfFlags;

    string minesLeftTemp = to_string(minesLeft);
    while (minesLeftTemp.length() < 3) {
        minesLeftTemp = "0" + minesLeftTemp;
    }

    // Allocate new memory for minesLeftText and update its value
    minesLeftText = new string(minesLeftTemp);
    *minesLeftText = minesLeftTemp;
}

// Handle mouse click events
void Toolbox::mouseClick(Event event) {
    // Check if a mouse button is pressed and the game is in the playing state
    if (event.type == Event::MouseButtonPressed && gameState->status == GameState::PLAYING) {
        // Get the current mouse position
        Vector2i mousePosition = Mouse::getPosition(window);

        // Calculate the position of the tile that the mouse is pointing to
        Vector2i tilePosition = Vector2i(mousePosition.x / 32, mousePosition.y / 32);

        // Check if the left mouse button is pressed
        if (event.mouseButton.button == Mouse::Left) {
            // Check if the calculated tile position is within the game board dimensions
            if (tilePosition.x < gameState->dimensions.x && tilePosition.y < gameState->dimensions.y) {
                // Get a pointer to the tile at the calculated position
                Tile* tile = &gameState->board[tilePosition.y][tilePosition.x];

                // Check the state of the tile
                if (tile->getState() == Tile::HIDDEN) {
                    // If the tile contains a mine, mark it as exploded, draw it, and set the game state to loss
                    if (tile->containsMine) {
                        tile->setState(Tile::EXPLODED);
                        tile->draw();
                        gameState->setPlayStatus(GameState::LOSS);
                    } else {
                        // If the tile is empty, reveal it, draw it, trigger left-click actions, and reveal its neighbors
                        if (tile->number == 0) {
                            tile->setState(Tile::REVEALED);
                            tile->draw();
                            tile->onClickLeft();
                            tile->revealNeighbors();
                        } else if (!tile->containsMine) {
                            // If the tile has a number, reveal and draw it
                            tile->setState(Tile::REVEALED);
                            tile->draw();
                        }
                    }

                    // Draw the entire game board after the left-click
                    for (int i = 0; i < gameState->dimensions.x; i++) {
                        for (int j = 0; j < gameState->dimensions.y; j++) {
                            Tile* tile = &gameState->board[j][i];
                            tile->draw();
                        }
                    }
                }
            }
        } else if (event.mouseButton.button == Mouse::Right) {
            // Check if the calculated tile position is within the game board dimensions
            if (tilePosition.x < gameState->dimensions.x && tilePosition.y < gameState->dimensions.y) {
                // Get a pointer to the tile at the calculated position
                Tile* tile = &gameState->board[tilePosition.y][tilePosition.x];

                // Check the state of the tile
                if (tile->getState() == Tile::HIDDEN) {
                    // Draw the flagged tile, increment the flag count, and trigger right-click actions
                    boardSprite.draw(*allSprites["tile_flagged"], Transform().translate(tilePosition.x * 32, tilePosition.y * 32));
                    gameState->numOfFlags++;
                    tile->onClickRight();
                } else if (tile->getState() == Tile::FLAGGED) {
                    // Draw the hidden tile, decrement the flag count, and trigger right-click actions
                    boardSprite.draw(*allSprites["tile_hidden.png"], Transform().translate(tilePosition.x * 32, tilePosition.y * 32));
                    gameState->numOfFlags--;
                    tile->onClickRight();
                }
            }
        }

        // Reset variables after processing mouse input
        mousePosition = Vector2i(0, 0);
        tilePosition = Vector2i(0, 0);
        boardSprite.display();
    }

    // Update the number of mines left
    minesLeft = gameState->mineCount - gameState->numOfFlags;

    // Convert the number of mines left to a string and ensure it has at least three characters
    string minesLeftTemp = to_string(minesLeft);
    while (minesLeftTemp.length() < 3 and minesLeft >= 0) {
        minesLeftTemp = "0" + minesLeftTemp;
    }

    // Update the displayed text for the number of mines left
    *minesLeftText = minesLeftTemp;

    // Check if the game has been won
    if (won()) {
        // Set the game state to win
        gameState->setPlayStatus(GameState::WIN);
    }
}

// Draw a mine tile based on debug mode
void Toolbox::drawMineTile(const Tile& tile, int x, int y) {
    const string spriteKey = (debugMode) ? "tile_mine" : "tile_hidden.png";
    const Transform transform = Transform().translate(x * tileWidth, y * tileHeight);
    boardSprite.draw(*allSprites[spriteKey], transform);
}

// Function for the Debug Mode button click
function<void(void)> Toolbox::clickDebugMode() {
    return [this]() {
        debugMode = !debugMode;
        const auto& dimensions = gameState->dimensions;
        const auto& board = gameState->board;
        for (int j = 0; j < dimensions.y; ++j) {
            for (int i = 0; i < dimensions.x; ++i) {
                const Tile& tile = board[j][i];

                if (tile.containsMine) {
                    drawMineTile(tile,  i, j);
                }
            }
        }
    };
}

// Function for the Button1 click
function<void(void)> Toolbox::clickButton1() {
    return [this]() {
        delete gameState;
        gameState = new GameState("../resources/boards/testboard1.brd");
        gameState->setPlayStatus(GameState::PLAYING);
        for(int i = 0; i < gameState->dimensions.x; i++) {
            for(int j = 0; j < gameState->dimensions.y; j++)
            {
                gameState->board[j][i].draw();
            }
        }
    };
}

// Function for the Button2 click
function<void(void)> Toolbox::clickButton2() {
    return [this]() {
        delete gameState;
        gameState = new GameState("../resources/boards/testboard2.brd");
        gameState->setPlayStatus(GameState::PLAYING);
        for(int i = 0; i < gameState->dimensions.x; i++) {
            for(int j = 0; j < gameState->dimensions.y; j++)
            {
                gameState->board[j][i].draw();
            }
        }
    };
}

// Function for the Button3 click
function<void(void)> Toolbox::clickButton3() {
    return [this]() {
        delete gameState;
        gameState = new GameState("../resources/boards/testboard3.brd");
        gameState->setPlayStatus(GameState::PLAYING);
        for(int i = 0; i < gameState->dimensions.x; i++) {
            for(int j = 0; j < gameState->dimensions.y; j++)
            {
                gameState->board[j][i].draw();
            }
        }
    };
}

// Destructor for Toolbox: releases memory for game state, mines left text, and sprites
Toolbox::~Toolbox() {
    delete gameState;
    delete minesLeftText;
    for (auto& sprite : allSprites) delete sprite.second->getTexture(), delete sprite.second;
}

// Function for the New Game button click
function<void(void)> Toolbox::clickNewGame() {
    return [this](){
        for(int i = 0; i < gameState->dimensions.x; i++) {
            for(int j = 0; j < gameState->dimensions.y; j++)
            {
                gameState->board[j][i].draw();
            }
        }
    };
}

// Check if the game is won by counting the revealed tiles
bool Toolbox::won() {
    int revealedTiles = 0;

    // Iterate through the board and count the revealed tiles
    for (const auto& row : gameState->board) {
        revealedTiles += count_if(row.begin(), row.end(), [](const Tile& tile) {
            return const_cast<Tile*>(&tile)->getState() == Tile::REVEALED;
        });
    }

    // Check if the number of revealed tiles is equal to the total number of tiles minus mines
    return revealedTiles == gameState->dimensions.x * gameState->dimensions.y - gameState->getMineCount();
}