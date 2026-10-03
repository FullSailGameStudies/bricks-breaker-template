#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>
#include <iostream>
#include <conio.h>

class Game
{
	Ball ball;
	Box paddle;
	bool end_game;
	bool win;
	int text_offset = -20;
	int screen_mid_width = (WINDOW_WIDTH / 2);
	int screen_mid_height = (WINDOW_HEIGHT / 2);
	int wrap_width = 40;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	std::vector<Box> bricks;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};