/***********************************************************************
* Programmer: Alba Raya Sanchez
* Class : CptS 122, Fall 2024; Lab Section 3
* Programming Assignment 9 - Battle Ship Game
* Date : December 4, 2024
* Description :
***********************************************************************/

#pragma once
#include "BoardClass.hpp"

class Player
{

public:
	// Constructor
	Player()
	{
		name = "";
		otherPlayer = nullptr;
	}

	// Getters
	string& get_name() { return name; }
	int get_numOfShots();
	Board& get_board() { return board; }
	Player* get_otherPlayer() { return otherPlayer; }

	// Setters
	void set_name(string& str) { name = str; }
	void set_board(Board newBoard) { board = newBoard; }
	void set_otherPlayer(Player* other) { otherPlayer = other; }

	// checks if player has won the game
	bool checkIfWinner();

	// place all 5 ships on the player's board
	virtual void placeAllShips(sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& gameplayBackground);
	// manages a turn of the game for this player
	virtual void playTurn() {}

	// resets all parameters from the player prior to restart a game
	virtual void resetPlayer();

	// Destructor
	~Player() {}

protected:

	string name;
	Board board;
	Player* otherPlayer;

private:
	char gen_dir();
	void gen_start_pt(char dir, int ship_length, Vector2i& startPos);

	// place ship
	void placeShip(Ship* ship);
};