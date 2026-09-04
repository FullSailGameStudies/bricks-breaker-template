#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>



class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	// complete
	std::vector<Box> bricks;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
	std::vector<Box> GenerateBricks(int _numOfBricks);
	void DamageBrick(Box& _brick);
	void StopBall();
};