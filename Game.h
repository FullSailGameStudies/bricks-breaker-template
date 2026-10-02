#pragma once
#include "Box.h"
#include "Ball.h"

#include <vector>

class Game
{
	Ball ball;
	Box paddle;

	std::vector<Box> bricks;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};