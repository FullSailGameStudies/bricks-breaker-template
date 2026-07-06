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

	gameOver = false;
	playerWin = false;

	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector
	//The first thing I want to do, in case of any confliction, is clear the bricks prior to each iteration. 
	bricks.clear();
	brickHits.clear();
	
	//Then, to make this brick 5 of them, I'll add this loop.
	for (int i = 0; i < 5; i++)
	{
		Box brick; //declared inside the loop to give a value to the vector
		brick.width = 10;
		brick.height = 2;
		//Since I can't have them all spawn in the same location, the X position needs to be relative. This means it'll be i * a value.
		//stdafx has a window width of 80, so it needs to split around that.
		// 5 bricks, 10 wide, means 30 leftover spaces between them. 30 / 6 gaps = 5 spaces per. Thus the 'spacing' variable is made.
		brick.x_position = (5 + (15*i));
		brick.y_position = 5;
		brick.doubleThick = true;
		brick.color = ConsoleColor::DarkGreen;

		//Had an issue at the end regarding the ball, fixed it this way.
		bricks.push_back(brick);
		brickHits.push_back(0);
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

	//Updated to stop updating on game end
	if (!gameOver)
	{
		ball.Update();
		CheckCollision();
	}

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
	//just like task 2, it's now a loop utilizing the local object and running the function on it.

	for (const Box& brick : bricks)
	{
		brick.Draw();
	}
	

	//Updated to both win and lose conditions
	if (gameOver)
	{
		Console::SetCursorPosition(WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2); //centers cursor

		if (playerWin)
		{
			std::cout << "Good job! Press R to play again.";
		}
		else
		{
			std::cout << "Better luck next time. Press R to play again.";
		}
	}
	Console::Lock(false); // moved down here to account for the new conditions.
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks

	//Another loop!
	for (int i = static_cast<int>(bricks.size()) - 1; i >= 0; i--) //Another Another loop! Updated this time to go backwards since it's erasing bricks.
	{
		if (bricks[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity)) //updated brick.Contains to bricks[i].Contains
		{
			bricks[i].color = ConsoleColor(bricks[i].color - 1);
			ball.y_velocity *= -1;

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector

			brickHits[i]++;
			
			if (brickHits[i] >= 3) //3 or more hits erase the ball
			{
				bricks.erase(bricks.begin() + i);
				brickHits.erase(brickHits.begin() + i);
			}
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset
	if (bricks.empty())
	{
		ball.moving = false;
		gameOver = true;
		playerWin = true;
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
	if (ball.y_position >= WINDOW_HEIGHT - 1) // if lower than the window, then it's a loss. Check Render for loss text
	{
		ball.moving = false;
		gameOver = true;
		playerWin = false;
	}
}
