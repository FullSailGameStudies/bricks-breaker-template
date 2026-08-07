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
	bricks.clear(); // This is going to clear out any od bricks if a Reset is called again.
	
	Box brick1; // This is the first set of box's out of 5.
	brick1.width = 10;
	brick1.height = 2;
	brick1.x_position = 0;
	brick1.y_position = 5;
	brick1.doubleThick = true;
	brick1.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick1);

	Box brick2; // This is the second set of box's out of 5.
	brick2.width = 10;
	brick2.height = 2;
	brick2.x_position = 12;
	brick2.y_position = 5;
	brick2.doubleThick = true;
	brick2.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick2);
	Box brick3; // This is the third set of box's out of 5.
	brick3.width = 10;
	brick3.height = 2;
	brick3.x_position = 24;
	brick3.y_position = 5;
	brick3.doubleThick = true;
	brick3.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick3);
	Box brick4; // This is the fourth set of box's out of 5.
	brick4.width = 10;
	brick4.height = 2;
	brick4.x_position = 36;
	brick4.y_position = 5;
	brick4.doubleThick = true;
	brick4.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick4);
	Box brick5; // This is the fifth set of box's out of 5.
	brick5.width = 10;
	brick5.height = 2;
	brick5.x_position = 48;
	brick5.y_position = 5;
	brick5.doubleThick = true;
	brick5.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick5);


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
	// if the ball isnt moving yet, it will keep it locked on to the paddle.
	if (!ball.moving && ball.y_position <= paddle.y_position)
	{
		ball.x_position = paddle.x_position + paddle.width / 2;
		ball.y_position = paddle.y_position - 1;
	}
	if (!bricks.empty() && ball.y_position < WINDOW_HEIGHT)
	{
		ball.Update();
		CheckCollision();
	} // Im having a lose message pop up immediatly, so this is to help make the message pop up once the game is initiated.
	
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
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i].Draw();
	}
	if (bricks.empty())
	{
		Console::SetCursorPosition(30, 15);
		Console::ForegroundColor(ConsoleColor::Green);     // This is todo 6. Victory!!
		std::cout << "You Win! Press R to reset.";

	}
	
	if (!ball.moving && !bricks.empty() && ball.y_position > paddle.y_position) // This fixed my bug of the lost condition popping up at the start of the game.
	{
		Console::SetCursorPosition(30, 15);
		Console::ForegroundColor(ConsoleColor::Red);        // This is todo 7. Defeat!!
		std::cout << "You Lose! Press R to reset.";
	}
	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[i].color = ConsoleColor(bricks[i].color - 1);
			ball.y_velocity *= -1;
			// This is going to loop through the vector of bricks and check if the ball collides with any single brick.


		// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			if (bricks[i].color == ConsoleColor::Black)
			{
				bricks.erase(bricks.begin() + i);
				break;
				// This portion will check if the brick has been hit 3 times, if so its color becomes black, and then removes it from the vector.

			}
		}
	}
	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
	{
		ball.y_velocity *= -1;
	} 
	// So i am having issues with the ball passing through the paddle, this will check a collision with the paddle.

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset


	if (bricks.empty()) {
		ball.moving = false;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
	if (ball.y_position >= WINDOW_HEIGHT)
	{
		ball.moving = false;
		ball.y_position = WINDOW_HEIGHT - 2; 
		ball.y_velocity = 0;
		ball.x_velocity = 0;
	}
}
