#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>

class Game
{
	Ball ball;
	Box paddle;

	//Store 5 bricks
	std::vector<Box> bricks;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)


public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};