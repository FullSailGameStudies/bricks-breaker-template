#pragma once
#include <vector>

#include "Box.h"
#include "Ball.h"

class Game
{
	Ball ball;
	Box paddle;

	bool isGameOver = false; // added variable to implement the lose condition -Brianna

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	//OLD = Box brick;

	//New
	std::vector<Box> bricks; 

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};