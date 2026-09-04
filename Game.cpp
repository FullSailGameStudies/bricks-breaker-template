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
	Box brick; 
	brick.width = 10;
	brick.height = 2;
	brick.x_position = 0;
	brick.y_position = 5;
	brick.doubleThick = true;
	brick.color = ConsoleColor::DarkGreen;
	
	for (int i = 0; i < numOfbricks; i++) 
	{
		
		bricks.push_back(brick);
		brick.x_position += 17; 
	}
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position -1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = true;
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
	{
		if (!bricks.empty()) 
		{
			bricks.clear();
		}
		Reset();
	}

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
	int count = 0; 
	while (count < bricks.size()) 
	{
		bricks[count].Draw();
		count++;
	}
	
	if (!ball.moving)
	{
		int Width_Center = WINDOW_WIDTH / 2;
		int Height_Center = WINDOW_HEIGHT / 2; 
		Console::SetCursorPosition(Width_Center,Height_Center-7);
		
		if (bricks.empty()) 
		{
			std::cout << "You Have Won.\n";
			
		}
		else if (!bricks.empty() && ball.y_position >= paddle.y_position+1)
		{
			std::cout << "You have lost!\n";
		}
		else 
		{
		
				std::cout << "Pause!\n";
			
		}
		
		Console::SetCursorPosition(Width_Center, Height_Center-5);
		std::cout << "Press 'R' to reset";
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	for (int i = 0; i < bricks.size(); i++) {
		if (bricks[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[i].color = ConsoleColor(bricks[i].color - 1);
			ball.y_velocity *= -1;

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			if (bricks[i].color == Black) 
			{
				bricks.erase(bricks.begin() + i);
			}

		}
	}
	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset
	if (bricks.empty()) 
	{
		ball.moving = false;
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
	if (ball.y_position == paddle.y_position+1) 
	{
		
		ball.moving = false;
		ball.x_velocity = 0;
		ball.y_velocity = 0;
	
	}
}
