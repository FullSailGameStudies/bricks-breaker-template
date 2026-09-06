#pragma once
#include "Box.h"
#include "Ball.h"
#include "vector"

class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	std::vector<Box> bricks;

	//flags for win/lose state
	bool victory = false;
	bool defeat = false;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};