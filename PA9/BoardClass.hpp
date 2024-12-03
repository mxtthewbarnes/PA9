/***********************************************************************
* Programmer: Alba Raya Sanchez
* Class : CptS 122, Fall 2024; Lab Section 3
* Programming Assignment 9 - Battle Ship Game
* Date : December 4, 2024
* Description : Board class for managing the Battleship game board.
***********************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

class Board {
public:
    Board();

    Vector2i get_displayPos() const;
    int get_num_rows() const { return num_rows; }
    int get_num_cols() const { return num_cols; }
    Ship& get_Ships(int index) { return *(shipList[index]); }

    void set_displayPos(const Vector2i& newStartDisplayPos);

    void initializeBoard();
    bool placeShip(Ship* ship);
    void displayBoard(sf::RenderWindow& window, const sf::Sprite& background) const;
    bool shootPosition(int row, int col);
    bool checkIfSunk(Ship& ship) const;
    bool checkIfAllSunk();
    int get_numOfShots() const;

    void manualPlaceShip(sf::RenderWindow& window, Ship* ship, float cellSize, Vector2i displayPos, const sf::Sprite& gameplayBackground);

    void highlightCells(sf::RenderWindow& window, int size, sf::Vector2i mousePos, int dir, float cellSize) const;

    ~Board();

private:
    
    int num_rows;
    int num_cols;
    char sea[10][10];
    Ship* shipList[5];
    Vector2i displayPos;

    int pos_ship(char id);
    void adjacent_cell(int* r, int* c, int dir);
};