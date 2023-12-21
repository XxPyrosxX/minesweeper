//
// Created by Rohun Gargya on 12/4/2023.
//

#include "Minesweeper.h"
#include "Toolbox.h"

int main(){
    // Entry point of the program
    return launch();
}

// Function to initialize Toolbox and start the game loop
int launch(){
    Toolbox& toolbox = Toolbox::getInstance();
    gameLoop();
    return 0;
}

// Function to restart the game
void restart(){
    err().rdbuf(NULL);
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    toolbox.gameState = new GameState();
    toolbox.debugMode = false;
}

// Function to render the game graphics
void render() {
    err().rdbuf(NULL);
    Toolbox &toolbox = Toolbox::getInstance();
    toolbox.window.clear();

    // Drawing game elements using sprites
    toolbox.window.draw(Sprite(toolbox.boardSprite.getTexture()));
    toolbox.window.draw(*toolbox.allSprites["debug.png"], Transform().translate(500, toolbox.dimensions.y));
    toolbox.window.draw(*toolbox.allSprites["test_1.png"], Transform().translate(564, toolbox.dimensions.y));
    toolbox.window.draw(*toolbox.allSprites["test_2.png"], Transform().translate(628, toolbox.dimensions.y));
    toolbox.window.draw(*toolbox.allSprites["Test_3.png"], Transform().translate(692, toolbox.dimensions.y));

    // Drawing the face sprite based on game state
    Sprite faceSprite;
    if (toolbox.gameState->getPlayStatus() == GameState::PlayStatus::LOSS) {
        faceSprite = *toolbox.allSprites["face_lose.png"];
    } else if (toolbox.gameState->getPlayStatus() == GameState::PlayStatus::WIN) {
        faceSprite = *toolbox.allSprites["face_win.png"];
    } else {
        faceSprite = *toolbox.allSprites["face_happy.png"];
    }
    toolbox.window.draw(faceSprite, Transform().translate(300, toolbox.dimensions.y));

    // Drawing the mines left count using digit sprites
    string digitString = "digit_";
    toolbox.window.draw(toolbox.minesLeft >= 0 && toolbox.minesLeft < 100 ? *toolbox.allSprites["digit_0"] : *toolbox.allSprites["digit_10"], Transform().translate(0, toolbox.dimensions.y));
    if(toolbox.minesLeft > 100) {
        digitString += (*toolbox.minesLeftText)[0];
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[1];
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(21, toolbox.dimensions.y));
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[2];
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(42, toolbox.dimensions.y));
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(0, toolbox.dimensions.y));
    } else if (toolbox.minesLeft < 0 and toolbox.minesLeft <= -10) {
        digitString = "digit_10";
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(0, toolbox.dimensions.y));
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[1];
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(21, toolbox.dimensions.y));
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[2];
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(42, toolbox.dimensions.y));
    } else if (toolbox.minesLeft < 0 and toolbox.minesLeft > -10) {
        digitString = "digit_10";
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(0, toolbox.dimensions.y));
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[1];
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(21, toolbox.dimensions.y));
    }
    else {
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[1];
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(21, toolbox.dimensions.y));
        digitString = "digit_";
        digitString += (*toolbox.minesLeftText)[2];
        toolbox.window.draw(*toolbox.allSprites[digitString], Transform().translate(42, toolbox.dimensions.y));
    }
    toolbox.window.display();
}

// Main game loop
int gameLoop() {
    err().rdbuf(NULL);
    Toolbox &toolbox = Toolbox::getInstance();
    while (toolbox.window.isOpen()) {
        Event event;
        Vector2i mousePosition;
        Vector2i tilePosition;
        Vector2i tileIndex;

        while (toolbox.window.pollEvent(event)) {
            mousePosition = Mouse::getPosition(toolbox.window);

            // Handling window closure event
            if (event.type == Event::Closed) {
                toolbox.window.close();
            }

            // Handling button clicks based on mouse position
            if (mousePosition.x >= 500 && mousePosition.x <= 500 + 64 && mousePosition.y >= toolbox.dimensions.y &&
                mousePosition.y <= toolbox.dimensions.y + 64 && event.type == Event::MouseButtonPressed &&
                event.mouseButton.button == Mouse::Left) {
                toggleDebugMode();
                mousePosition = Vector2i(0, 0);
            } else if (mousePosition.x >= 300 && mousePosition.x <= 300 + 64 && mousePosition.y >= toolbox.dimensions.y &&
                       mousePosition.y <= toolbox.dimensions.y + 64 && event.type == Event::MouseButtonPressed &&
                       event.mouseButton.button == Mouse::Left) {
                restart();
                toolbox.newGameButton->onClick();
                mousePosition = Vector2i(0, 0);
            } else if (mousePosition.x >= 564 && mousePosition.x <= 564 + 64 && mousePosition.y >= toolbox.dimensions.y &&
                       mousePosition.y <= toolbox.dimensions.y + 64 && event.type == Event::MouseButtonPressed &&
                       event.mouseButton.button == Mouse::Left) {
                restart();
                mousePosition = Vector2i(0, 0);
                toolbox.testButton1->onClick();
            } else if (mousePosition.x >= 628 && mousePosition.x <= 628 + 64 && mousePosition.y >= toolbox.dimensions.y &&
                       mousePosition.y <= toolbox.dimensions.y + 64 && event.type == Event::MouseButtonPressed &&
                       event.mouseButton.button == Mouse::Left) {
                restart();
                mousePosition = Vector2i(0, 0);
                toolbox.testButton2->onClick();
            } else if (mousePosition.x >= 692 && mousePosition.x <= 692 + 64 && mousePosition.y >= toolbox.dimensions.y &&
                       mousePosition.y <= toolbox.dimensions.y + 64 && event.type == Event::MouseButtonPressed &&
                       event.mouseButton.button == Mouse::Left) {
                restart();
                mousePosition = Vector2i(0, 0);
                toolbox.testButton3->onClick();
            }

            toolbox.mouseClick(event);
        }

        // Rendering the game graphics
        render();
    }

    return 0;
}

// Function to toggle debug mode
void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.debugButton->onClick();
}

// Function to get the current debug mode
bool getDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    return toolbox.debugButton;
}