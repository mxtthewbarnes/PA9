#include "ComputerClass.hpp"


Computer::Computer()
    : targetDetectedStart(-1, -1), targetDetectedEnd(-1, -1)
{
}

void Computer::placeAllShips(sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& gameplayBackground) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //display bg and update as ships are being placed
        window.clear();
        board.displayBoard(window, gameplayBackground);
        window.display();

        
        placeAllShips(board);

        break; //exit after placing ships 
    }
}

void Computer::placeAllShips(Board& board) {
    Ship* newShip = nullptr;
    srand(static_cast<unsigned>(time(0)));

    std::vector<std::pair<std::string, int>> shipData = {
        {"Carrier", 5},
        {"Battleship", 4},
        {"Cruiser", 3},
        {"Submarine", 3},
        {"Destroyer", 2}
    };

    //ship id's 
    std::vector<char> shipIDs = { 'c', 'b', 'r', 's', 'd' }; 

    for (size_t i = 0; i < shipData.size(); ++i) {
        bool placed = false;

        while (!placed) {
            int row = rand() % board.get_num_rows();
            int col = rand() % board.get_num_cols();
            int direction = 1 + (rand() % 4);

            newShip = new Ship(shipData[i].first, shipData[i].second, shipIDs[i], Vector2i(row, col), direction);
            placed = board.placeShip(newShip);

            if (!placed) {
                delete newShip;
            }
        }
    }
}

void Computer::playTurn(Board& opponentBoard) {
    bool validShot = false;

    while (!validShot) {
        int row = rand() % opponentBoard.get_num_rows();
        int col = rand() % opponentBoard.get_num_cols();
        std::cout << "Computer trying to shoot at (" << row << ", " << col << ")" << std::endl;  
        validShot = opponentBoard.shootPosition(row, col);
    }
}

void Computer::resetPlayer() {
    Player::resetPlayer();
    targetDetectedStart = Vector2i(-1, -1);
    targetDetectedEnd = Vector2i(-1, -1);
}