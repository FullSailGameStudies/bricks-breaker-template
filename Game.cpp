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
	// Complete
	bricks.clear();
	bricks = GenerateBricks(5);
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
	//complete

	for (int currBrick = 0; currBrick < bricks.size(); ++currBrick)
		bricks[currBrick].Draw();

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	for (int currBrick = 0; currBrick < bricks.size(); ++currBrick) {
		if (bricks[currBrick].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[currBrick].color = ConsoleColor(bricks[currBrick].color - 1);
			ball.y_velocity *= -1;

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			DamageBrick(bricks[currBrick]);
			if (bricks[currBrick].color == Black)
				bricks.erase(bricks.begin() + currBrick);
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset

	if (bricks.empty()) {
		Console::WordWrap(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, WINDOW_WIDTH, "Victory: \tPress \"R\" To Play Again");
		StopBall();
	}
		

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
	if (ball.y_position == WINDOW_HEIGHT) {
		Console::WordWrap(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, WINDOW_WIDTH, "Defeat: \tPress \"R\" To Play Again");
		StopBall();
	}
}

std::vector<Box> Game::GenerateBricks(int _numOfBricks)
{
	std::vector<Box> output;


	Box tempBrick;
	tempBrick.width = 10;
	tempBrick.height = 2;
	tempBrick.x_position = 0;
	tempBrick.y_position = 5;
	tempBrick.doubleThick = true;
	tempBrick.color = ConsoleColor::DarkGreen;
	int offSet = (WINDOW_WIDTH) / _numOfBricks;
	
	output.push_back(tempBrick);
	

	for (int i = 1; i < _numOfBricks; ++i) {

		tempBrick.x_position = i*offSet;
		output.push_back(tempBrick);
	}



	return output;
}

void Game::DamageBrick(Box& _brick)
{
	_brick.DecreaseBoxHealth();
	if (_brick.boxHealth == 2) {
		_brick.color = Blue;
	}
	else if (_brick.boxHealth == 1)
		_brick.color = DarkBlue;
	else if (_brick.boxHealth == 0)
		_brick.color = Black;
}

void Game::StopBall()
{
	ball.x_velocity = 0;
	ball.y_velocity = 0;
}


