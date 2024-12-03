
#include "HumanClass.hpp"


int Human::scan_board_pos_dir(Vector2i& pos, sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& background) {
    bool startSelected = false; 
    sf::Vector2i mousePos;
    sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
    highlight.setFillColor(sf::Color(0, 255, 0, 100)); 
    highlight.setOutlineThickness(2);
    highlight.setOutlineColor(sf::Color::Black);

    int direction = 0; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //detecting mouse 
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePos = sf::Mouse::getPosition(window);

                int col = static_cast<int>((mousePos.x - displayPos.x) / cellSize);
                int row = static_cast<int>((mousePos.y - displayPos.y) / cellSize);

                if (row >= 0 && row < board.get_num_rows() && col >= 0 && col < board.get_num_cols()) {
                    if (!startSelected) {
                        //set start position 
                        pos.x = row;
                        pos.y = col;
                        startSelected = true;
                        std::cout << "Start position selected at (" << row << ", " << col << ")" << std::endl;
                    }
                    else {
                        //second click detemrines direction of ship 
                        int newCol = static_cast<int>((mousePos.x - displayPos.x) / cellSize);
                        int newRow = static_cast<int>(std::round((mousePos.y - displayPos.y) / cellSize));
                        if (newRow == pos.x && newCol > pos.y) {
                            direction = 1; //right
                        }
                        else if (newRow == pos.x && newCol < pos.y) {
                            direction = 2; //left
                        }
                        else if (newCol == pos.y && newRow > pos.x) {
                            direction = 3; //down
                        }
                        else if (newCol == pos.y && newRow < pos.x) {
                            direction = 4; //up
                        }

                        if (direction != 0) {
                            std::cout << "Direction selected: " << direction << std::endl;
                            return direction; 
                        }
                        else {
                            std::cout << "Invalid direction. Please click a valid adjacent cell." << std::endl;
                        }
                    }
                }
                else {
                    std::cout << "Invalid click. Please select a cell within the grid." << std::endl;
                }
            }
        }

        window.clear();
        board.displayBoard(window, background); 
        if (startSelected) {
            highlight.setPosition(displayPos.x + pos.y * cellSize, displayPos.y + pos.x * cellSize);
            window.draw(highlight);
        }
        window.display();
    }

    return direction; 
}


void Human::placeShip(Ship& ship, sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& background) {
    Vector2i pos;
    bool validPlacement = false;

    while (!validPlacement) {
        ship.setDirection(scan_board_pos_dir(pos, window, board, cellSize, displayPos, background));
        ship.setStartPos(pos);

        if (board.placeShip(&ship)) {
            validPlacement = true;
        }
        else {
            std::cout << "Invalid placement. Try again!" << std::endl;
        }

        window.clear();
        board.displayBoard(window, background); 
        board.highlightCells(window, ship.getSize(), pos, ship.getDirection(), cellSize);
        window.display();
    }
}

void Human::placeAllShips(sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& background) {
    Ship* newShip = nullptr;

    newShip = new Ship("Carrier", 5, 'c', Vector2i(0, 0), 1);
    placeShip(*newShip, window, board, cellSize, displayPos, background);
    newShip = nullptr;

    newShip = new Ship("Battleship", 4, 'b', Vector2i(0, 0), 1);
    placeShip(*newShip, window, board, cellSize, displayPos, background);
    newShip = nullptr;

    newShip = new Ship("Cruiser", 3, 'r', Vector2i(0, 0), 1);
    placeShip(*newShip, window, board, cellSize, displayPos, background);
    newShip = nullptr;

    newShip = new Ship("Submarine", 3, 's', Vector2i(0, 0), 1);
    placeShip(*newShip, window, board, cellSize, displayPos, background);
    newShip = nullptr;

    newShip = new Ship("Destroyer", 2, 'd', Vector2i(0, 0), 1);
    placeShip(*newShip, window, board, cellSize, displayPos, background);
    newShip = nullptr;
}

void Human::playTurn(Board& opponentBoard, sf::RenderWindow& window, float cellSize, Vector2i displayPos, const sf::Sprite& background) {
    bool validShot = false;

    while (!validShot && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int col = static_cast<int>(std::round((mousePos.x - displayPos.x) / cellSize));
                int row = static_cast<int>(std::round((mousePos.y - displayPos.y) / cellSize));

                if (row >= 0 && row < opponentBoard.get_num_rows() &&
                    col >= 0 && col < opponentBoard.get_num_cols()) {
                    validShot = opponentBoard.shootPosition(row, col);
                    if (!validShot) {
                        std::cout << "Invalid shot. Try again!" << std::endl;
                    }
                }
            }
        }

        window.clear();
        opponentBoard.displayBoard(window, background); 
        window.display();
    }
}

void Human::resetPlayer()
{
	Player::resetPlayer();
}