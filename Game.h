#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>

enum STATE {
	PLAY = 0,
	WIN,
	LOSE
};

class Game
{
	Ball ball;
	Box paddle;
	STATE state = PLAY;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	std::vector<Box> bricks;
	Box brick;


public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};