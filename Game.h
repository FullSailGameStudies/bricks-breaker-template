#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>
#include <Windows.h>

class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value) *DONE*
	std::vector<Box> bricks;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
	void PositionText(short x, short y, std::string text);
};