#pragma once
#include <vector>
#include "Box.h"
#include "Ball.h"

class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	Box brick;
	std::vector<Box>bricks;

public:
	Game();
	bool Update();
	//victory toggle
	bool victory = false;
	//defeat toggle
	bool defeat = false;
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};