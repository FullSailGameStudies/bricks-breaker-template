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

	// TODO #2 - Add this brick and 4 more bricks to the vector
	// Added the Box brick to this location to push_back to the vector.
	Box brick;
	brick.width = 10;
	brick.height = 2;
	brick.x_position = 0;
	brick.y_position = 5;
	brick.doubleThick = true;
	brick.color = ConsoleColor::DarkGreen;
	// Added a for loop here to add a total of 5 bricks per instruction with a 5 pixel gap in between.

	// Testing
	if (bricks.size() > 0)
	{
		bricks.erase(bricks.begin(), bricks.end());
	}
	// End testing
	// Found a workaround to remove bricks in the meantime with the above test, will create an actual fix at a future date.

	for (size_t i = 0; i < 5; i++)
	{
		bricks.push_back(brick);
		brick.x_position = brick.x_position + 16/*(WINDOW_WIDTH / 5)*/;
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
	// Comment out single draw, to draw the full vector using a for loop.
	for (size_t i = 0; i < bricks.size(); i++)
	{
		bricks[i].Draw();
	}
	// brick.Draw();

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	// Used a for loop at the beginning to check the full vector.
	// All commented out code for bricks color is for debugging purposes.
	for (size_t i = 0; i < bricks.size(); i++)
	{
		if (bricks[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[i].color = ConsoleColor(bricks[i].color - 1);
			//bricks[i].color = ConsoleColor(bricks[i].color - 2);
			ball.y_velocity *= -1;

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			// Used the ConsoleColor code to erase an element from a vector.
			if (bricks[i].color == ConsoleColor::Black)
			{
				bricks.erase(bricks.begin() + i);
				//bricks.erase(bricks.begin(), bricks.end());
			}
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset
	// Creating a boxed message after winning/losing.
	Box messageBox;
	messageBox.width = 40;
	messageBox.height = 3;
	messageBox.x_position = WINDOW_WIDTH / 2 - (messageBox.width / 2);
	messageBox.y_position = WINDOW_HEIGHT / 3 - (messageBox.height / 2);
	messageBox.doubleThick = true;
	messageBox.color = ConsoleColor::White;

	// Using if statement to check if any elements left on vector.
	if (bricks.size() == 0)
	{
		Game::Render();
		ball.moving = false;
		messageBox.color = ConsoleColor::Blue;
		messageBox.Draw();
		std::string winMessage = "You won! Press 'R' to reset.";
		Console::WordWrap(messageBox.x_position + 5, messageBox.y_position + 1, messageBox.width - 2, winMessage.c_str());
		while (bricks.size() == 0)
		{
			if (GetAsyncKeyState('R') & 0x1)
				Reset();
		}
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
	// Using if statement to check if ball is at window's max height.
	if (ball.y_position == paddle.y_position)
	{
		bricks.clear();
		if (bricks.size() > 0)
		{

		}
		ball.moving = false;
		messageBox.color = ConsoleColor::Red;
		messageBox.Draw();
		std::string loseMessage = "You lost... Press 'R' to reset.";
		Console::WordWrap(messageBox.x_position + 3, messageBox.y_position + 1, messageBox.width - 2, loseMessage.c_str());
		while (ball.y_position == paddle.y_position)
		{
			if (GetAsyncKeyState('R') & 0x1)
				Reset();
		}
	}
}
