#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>

enum class GameState
{
	Playing,
	Won,
	Lost
};

class Game
{
	Ball ball;
	Box paddle;
	GameState state = GameState::Playing;
	// #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	std::vector<Box> bricks;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};