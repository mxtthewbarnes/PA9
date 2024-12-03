#include "Menu.hpp"
#include "HumanClass.hpp"
#include "ComputerClass.hpp"
#include <SFML/Graphics.hpp>
#include "BoardClass.hpp"

using std::cout;
using std::endl;
using sf::Vector2i;

enum status {
    START, GAMEPLAY, OVER
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Battleship");
    Menu menu(&window);
    Human humanPlayer;
    Computer computerPlayer;


    //load background pic for menu
    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("C:/Users/matthewbarnes/source/repos/PA9/PA9/assets/main-menu.png")) {
        cout << "Error: Unable to load menu background texture. Check file path." << endl;
        return -1;
    }
    sf::Sprite menuBackground(menuBackgroundTexture);

    //loads background pic for gameplay (the ocean) 
    sf::Texture gameplayBackgroundTexture;
    if (!gameplayBackgroundTexture.loadFromFile("C:/Users/matthewbarnes/source/repos/PA9/PA9/assets/image-copy.png")) {
        cout << "Error: Unable to load gameplay background texture. Check file path." << endl;
        return -1;
    }
    sf::Sprite gameplayBackground(gameplayBackgroundTexture);

    //initialize the two boards
    Board playerBoard;
    Board computerBoard;

    //calculates cell sizes and and board display
    float cellWidth = window.getSize().x / 10.0f;
    float cellHeight = window.getSize().y / 10.0f;
    float cellSize = std::min(cellWidth, cellHeight);
    Vector2i playerBoardPos(50, 50);
    Vector2i computerBoardPos(50, 50);

    playerBoard.set_displayPos(playerBoardPos);
    computerBoard.set_displayPos(computerBoardPos);

    //set current state to START (or the beginning of gameplau) 
    status currentState = START;
    bool playerTurn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentState == OVER && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        switch (currentState) {
        case START:
            menu.mouseHover();
            window.clear();
            window.draw(menuBackground);
            menu.render();
            window.display();

            if (menu.handleEvent(event)) {
                currentState = GAMEPLAY;
                cout << "Starting gameplay..." << endl;

                //player & computer place ships 
                humanPlayer.placeAllShips(window, playerBoard, cellSize, playerBoardPos, gameplayBackground);
                computerPlayer.placeAllShips(window, computerBoard, cellSize, computerBoardPos, gameplayBackground);

                ////resize window so both user and computers grids are visible to user
                //window.setSize(sf::Vector2u(1600, 1000));
                cellWidth = window.getSize().x / 10.0f;
                cellHeight = window.getSize().y / 10.0f;
                cellSize = std::min(cellWidth, cellHeight);

            }
            break;

        case GAMEPLAY:
            //clear window, set background picture
            window.clear();
            window.draw(gameplayBackground);

            //beginning gameplay 
            if (playerTurn) {
                cout << "players turn" << endl;
                humanPlayer.playTurn(computerBoard, window, cellSize, computerBoardPos, gameplayBackground);
                if (computerBoard.checkIfAllSunk()) {
                    cout << "Player wins!" << endl;
                    currentState = OVER;
                }
                playerTurn = false;
            }
            else {
                cout << "Opoonents turn" << endl;
                computerPlayer.playTurn(playerBoard);
                if (playerBoard.checkIfAllSunk()) {
                    cout << "Computer wins!" << endl;
                    currentState = OVER;
                }
                playerTurn = true;
            }

            playerBoard.displayBoard(window, gameplayBackground);
            computerBoard.displayBoard(window, gameplayBackground);
            window.display();
            break;

        case OVER:
            window.clear();
            sf::Font font;
            if (!font.loadFromFile("C:/Users/matthewbarnes/source/repos/PA9/PA9/assets/minecraft.ttf")) {
                cout << "Error: Unable to load font for game over screen. Check file path." << endl;
                return -1;
            }

            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(50);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setString("Game Over!\nPress ESC to Quit.");
            gameOverText.setPosition(300, 450); 
            window.draw(gameOverText);
            window.display();
            break;
        }
    }

    return 0;
}