#pragma once
#include <string>
#include <vector>
#include "Box.h"
#include "Ball.h"

class Game
{
	Ball ball;
	Box paddle;
	std::vector<Box> bricks;
	std::string endMessage;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	Box brick;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};