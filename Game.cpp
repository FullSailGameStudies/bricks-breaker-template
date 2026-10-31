#include "stdafx.h"
#include "Game.h"
#include <string>

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

	// TODO #2 - Add this brick and 4 more bricks to the vector
	won = false;
	lost = false;
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

	// TODO #3 - Update render to render all bricks
	for (const Box& brick : bricks)
	{
		brick.Draw();
	}

	// Victory Message from Todo #6
	if (won)
	{
		const std::string message = "You win! Press 'R' to play again.";
		const int textX =
			(WINDOW_WIDTH - static_cast<int>(message.length())) / 2;

		Console::ForegroundColor(ConsoleColor::White);
		Console::SetCursorPosition(textX, WINDOW_HEIGHT / 2);
		std::cout << message;
	}

	//You lose message for Todo #7
	if (lost)
	{
		const std::string message = "You lose. Press 'R' to play again.";
		const int textX =
			(WINDOW_WIDTH - static_cast<int>(message.length())) / 2;

		Console::ForegroundColor(ConsoleColor::White);
		Console::SetCursorPosition(textX, WINDOW_HEIGHT / 2);
		std::cout << message;
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	for (auto brick = bricks.begin(); brick != bricks.end(); ++brick)
	{
		if (brick->Contains(
			ball.x_position + ball.x_velocity,
			ball.y_position + ball.y_velocity))
		{
			brick->color = static_cast<ConsoleColor>(brick->color - 1);
			ball.y_velocity *= -1;

			// TODO #5 - Remove the brick after three hits
			if (brick->color == ConsoleColor::Black)
			{
				bricks.erase(brick);
			}

			break;
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset
	if (bricks.empty())
	{
		won = true;
		ball.moving = false;
		return;
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
	if (ball.y_position >= WINDOW_HEIGHT - 1)
	{
		lost = true;
		ball.moving = false;
	}
}