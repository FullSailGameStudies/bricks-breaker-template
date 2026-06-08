#include "stdafx.h"
#include "Game.h"



Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::Clear();
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
	
	if (bricks.size() != 0) {
		bricks.clear();
	}
	
	for (size_t i = 1; i < 6; ++i) {
		Box temp;
		temp.width = 10;
		temp.height = 2;
		temp.x_position = (i * 14);
		temp.y_position = 5;
		temp.doubleThick = true;
		temp.color = ConsoleColor::DarkCyan;
		bricks.push_back(temp);
	}

	
	
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position;
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
	
	if (bricks.size() != 0) {
		paddle.Draw();
		ball.Draw();
	}

	// TODO #3 - Update render to render all bricks
	for (size_t i = 0; i < bricks.size(); i++) {
		bricks[i].Draw();
	}
	Console::Lock(false);

	if (bricks.size() == 0) {
		Console::Clear;
		std::string text = "You win! Press 'R' to play again";
		int width = Console::WindowWidth();
		int height = Console::WindowHeight();
		width /= 2;
		height /= 4;
		//std::string(size_type count, char ch);
		std::cout << std::string(height, '\n') << std::string(width, ' ') << text;
		return;
	}

	int windowHeight = Console::WindowHeight();
	if ((ball.y_position) == windowHeight) {
		Console::Clear;
		std::string text = "You lose. Press 'R' to play again";
		int width = Console::WindowWidth();
		int height = Console::WindowHeight();
		width /= 2;
		height /= 4;
		//std::string(size_type count, char ch);
		std::cout << std::string(height, '\n') << std::string(width, ' ') << text;
		return;
	}
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

	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset

	int windowHeight = Console::WindowHeight();
	if ((ball.y_position) == windowHeight) {
		ball.moving = false;
	}
}
