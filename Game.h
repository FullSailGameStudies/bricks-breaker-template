#pragma once
#include "Box.h"
#include "Ball.h"
// Added a vector line to include vectors.
#include <vector>

class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	// Added a vector and commented out "Box brick;" to add more bricks.
	// This is a work in progress but changes to all "brick" phrasing will change to "bricks" to utilize the vector.
	std::vector<Box> bricks;
	//Box brick;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};