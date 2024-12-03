/*
                Matthew Barnes
            CPTS 122 - Lab section 1
              PA 9 - BATTLE SHIP  
*/

#pragma once
#include "PlayerBaseClass.hpp"
#include "BoardClass.hpp"

#include <vector>
#include <utility> 

class Computer : public Player
{
private:
    Vector2i targetDetectedStart;
    Vector2i targetDetectedEnd;

public:
    Computer();

    void placeAllShips(sf::RenderWindow& window, Board& board, float cellSize, Vector2i displayPos, const sf::Sprite& gameplayBackground) override;

    void placeAllShips(Board& board);

    void playTurn(Board& opponentboard);

    void resetPlayer();

    ~Computer() {};
};