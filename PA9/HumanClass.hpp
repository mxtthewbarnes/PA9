/***********************************************************************
* Programmer: Alba Raya Sanchez
* Class : CptS 122, Fall 2024; Lab Section 3
* Programming Assignment 9 - Battle Ship Game
* Date : December 4, 2024
* Description :
***********************************************************************/

#pragma once
#include "PlayerBaseClass.hpp"

class Human :public Player
{
public:

	// place all 5 ships on the player's board
	void placeAllShips(sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& background);

	// manages a turn of the game for this player
	virtual void playTurn(Board& opponentBoard, sf::RenderWindow& window, float cellSize, Vector2i displayPos, const sf::Sprite& background);


	// resets all parameters from the player prior to restart a game
	virtual void resetPlayer();

private:
	// scan start position and output in pos
	// returns direction pointed by mouse as well
	void placeShip(Ship& ship, sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& background);

	int scan_board_pos_dir(Vector2i& pos, sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& background);

	};