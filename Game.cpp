#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	for (int currBrickIndex = 0; currBrickIndex < 5; currBrickIndex++) {
		Box currBrick;
		currBrick.width = 10;
		currBrick.height = 2;
		currBrick.x_position = 15 * currBrickIndex;
		currBrick.y_position = 5;
		currBrick.doubleThick = true;
		currBrick.color = ConsoleColor::DarkGreen;
		
		bricks.push_back(currBrick);
	}
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering, including text, should occur in the Render function
void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();
	
	paddle.Draw();
	ball.Draw();

	for (int currBrickIndex = 0; currBrickIndex < bricks.size(); currBrickIndex++) {
		bricks[currBrickIndex].Draw();
	}

	if (bricks.empty()) {
		Console::WordWrap(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3, 33, "You Win! Press 'R' to Play Again!");
	}

	if (ball.y_position > paddle.y_position + 1) {
		Console::WordWrap(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3, 34, "You Lose, Press 'R' to Play Again!");
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{
	for (int currBrickIndex = 0; currBrickIndex < bricks.size(); currBrickIndex++) {
		if (bricks[currBrickIndex].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[currBrickIndex].color = ConsoleColor(bricks[currBrickIndex].color - 1);
			ball.y_velocity *= -1;

			if (bricks[currBrickIndex].color == ConsoleColor::Black) {
				bricks.erase(bricks.begin() + currBrickIndex);
			}
		}

		if (bricks.empty()) {
			ball.moving = false;
		}


		if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
		{
			ball.y_velocity *= -1;
		}

		
		if (ball.y_position > paddle.y_position + 1) {
			ball.moving = false;
		}
	}
}
