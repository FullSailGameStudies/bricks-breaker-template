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

	bricks.clear();
	for (int i = 0; i < 5; ++i)
	{
		Box brick;
		brick.width = 10;
		brick.height = 2;
		brick.x_position = 5 + i * 15;
		brick.y_position = 5;
		brick.doubleThick = true;
		brick.color = ConsoleColor::DarkCyan;
		bricks.push_back(brick);
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

	for (const Box& brick : bricks)
		brick.Draw();

	if (bricks.empty())
	{
		Console::ForegroundColor(White);
		Console::SetCursorPosition(23, 20);
		std::cout << "You win! Press 'R' to play again.";
	}
	else if (ball.y_position >= WINDOW_HEIGHT - 1)
	{
		Console::ForegroundColor(White);
		Console::SetCursorPosition(23, 20);
		std::cout << "You lose. Press 'R' to play again.";
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{
	for (auto it = bricks.begin(); it != bricks.end(); ++it)
	{
		if (it->Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			it->color = ConsoleColor(it->color - 1);
			ball.y_velocity *= -1;

			if (it->color == Black)
				bricks.erase(it);

			break;
		}
	}

	if (bricks.empty())
		ball.moving = false;

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	if (ball.y_position >= WINDOW_HEIGHT - 1)
		ball.moving = false;
}
