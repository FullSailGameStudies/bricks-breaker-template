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

	
	brick.clear();
	for (int i = 0; i < 5; i++)
	{
		Box b;
		b.width = 10;
		b.height = 2;
		b.x_position = 0;
		b.y_position = 5;
		b.doubleThick = true;
		b.color = ConsoleColor::DarkGreen;
		b.x_position = i * (WINDOW_WIDTH / 5);
		brick.push_back(b);
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

	
	for (int i = 0; i < brick.size(); i++)
	{
		brick[i].Draw();
	}

	if (brick.size() == 0)
	{
		Console::WordWrap(WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2, 30, "You win! Press 'R' to play again.");
	}

	if (ball.y_position >= WINDOW_HEIGHT - 1)
	{
		Console::WordWrap(WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2, 30, "You lose. Press 'R' to play again.");
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{

	for (int i = 0; i < brick.size(); i++)
	{
		if (brick[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			brick[i].color = ConsoleColor(brick[i].color - 1);
			ball.y_velocity *= -1;

			if (brick[i].color == ConsoleColor::Black)
			{
				brick.erase(brick.begin() + i);
				i--;
			}
		}
	}



	if (brick.size() == 0)
	{
		ball.moving = false;
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	if (ball.y_position >= WINDOW_HEIGHT - 1)
	{
		ball.moving = false;
	}
}
