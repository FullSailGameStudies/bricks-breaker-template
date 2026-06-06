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
	Box zero, one, two, three, four;
	zero.width = 10;
	zero.height = 2;
	zero.x_position = 0;
	zero.y_position = 5;
	zero.doubleThick = true;
	zero.color = ConsoleColor::DarkGreen;

	one.width = 10;
	one.height = 2;
	one.x_position = 15;
	one.y_position = 5;
	one.doubleThick = true;
	one.color = ConsoleColor::DarkGreen;

	two.width = 10;
	two.height = 2;
	two.x_position = 30;
	two.y_position = 5;
	two.doubleThick = true;
	two.color = ConsoleColor::DarkGreen;

	three.width = 10;
	three.height = 2;
	three.x_position = 45;
	three.y_position = 5;
	three.doubleThick = true;
	three.color = ConsoleColor::DarkGreen;

	four.width = 10;
	four.height = 2;
	four.x_position = 60;
	four.y_position = 5;
	four.doubleThick = true;
	four.color = ConsoleColor::DarkGreen;
	
	bricks.push_back(zero);
	bricks.push_back(one);
	bricks.push_back(two);
	bricks.push_back(three);
	bricks.push_back(four);
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
	for (size_t i = 0; i < bricks.size(); i++) {
		bricks[i].Draw();
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
			if (bricks[i].color == ConsoleColor::Black) {
				bricks.erase(bricks.begin() + i);
			}
		}
	}
	

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset
	
	if (bricks.size() == 0) {
		ResetBall();
		ball.moving = false;
		int width = Console::WindowWidth();
		int spaces = (width - 31) / 2;
		std::cout << std::string(spaces, ' ') << "You win! Press ‘R’ to play again";

	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
}
