#include "PlayerBaseClass.hpp"
#include <iostream>

// Check if all ships on the board are sunk
bool Player::checkIfWinner()
{
    return board.checkIfAllSunk();
}

// Place a single ship on the board
void Player::placeShip(Ship* ship)
{
    int dir = 0;

    do {
        // Generate a random direction
        ship->setDirection(gen_dir());

        // Generate a random starting position
        gen_start_pt(dir, ship->getSize(), ship->getStartPos());
    } while (!board.placeShip(ship));
}

// Place all ships on the board (default implementation for Player)
void Player::placeAllShips(sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& gameplayBackground) {
    Ship* newShip = nullptr;

    newShip = new Ship("Carrier", 5, 'c', Vector2i(0, 0), 1);
    board.manualPlaceShip(window, newShip, cellSize, displayPos, gameplayBackground);

    newShip = new Ship("Battleship", 4, 'b', Vector2i(0, 0), 1);
    board.manualPlaceShip(window, newShip, cellSize, displayPos, gameplayBackground);

    newShip = new Ship("Cruiser", 3, 'r', Vector2i(0, 0), 1);
    board.manualPlaceShip(window, newShip, cellSize, displayPos, gameplayBackground);

    newShip = new Ship("Submarine", 3, 's', Vector2i(0, 0), 1);
    board.manualPlaceShip(window, newShip, cellSize, displayPos, gameplayBackground);

    newShip = new Ship("Destroyer", 2, 'd', Vector2i(0, 0), 1);
    board.manualPlaceShip(window, newShip, cellSize, displayPos, gameplayBackground);
}

// Generate a random direction for ship placement
char Player::gen_dir()
{
    // 1: left, 2: right, 3: up, 4: down
    return 1 + (rand() % 4);
}

// Generate a random starting position for a ship
void Player::gen_start_pt(char dir, int ship_length, Vector2i& startPos)
{
    if (dir == 1) // left
    {
        startPos.x = rand() % board.get_num_rows();
        startPos.y = ship_length + (rand() % (board.get_num_cols() - ship_length + 1));
    }
    if (dir == 2) // right
    {
        startPos.x = rand() % board.get_num_rows();
        startPos.y = rand() % (board.get_num_cols() - ship_length + 1);
    }
    if (dir == 3) // up
    {
        startPos.x = ship_length + (rand() % (board.get_num_rows() - ship_length + 1));
        startPos.y = rand() % board.get_num_cols();
    }
    if (dir == 4) // down
    {
        startPos.x = rand() % (board.get_num_rows() - ship_length + 1);
        startPos.y = rand() % board.get_num_cols();
    }
}

// Returns the number of shots tried by this player
int Player::get_numOfShots()
{
    return board.get_numOfShots();
}

// Resets the player's board before starting a new game
void Player::resetPlayer()
{
    board.initializeBoard();
}