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
    bricks.clear();

    for (int i = 0; i < 5; i++)
    {
        Box brick;

        brick.width = 10;

        brick.height = 2;

        brick.x_position = 0 + (i * 15);

        brick.y_position = 10;

        brick.doubleThick = true;

        brick.color = ConsoleColor::DarkGreen;

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
    for (size_t i = 0; i < bricks.size(); i++)
    {
        bricks[i].Draw();
    }

    if (bricks.empty())
    {
        const char* message = "You Win! Press 'R' to play again.";

        int messageX = (WINDOW_WIDTH - 33) / 2;

        int messageY = WINDOW_HEIGHT / 2;


        Console::SetCursorPosition(messageX, messageY);

        Console::ForegroundColor(ConsoleColor::White);

        std::cout << message;
    }
    
    if (ball.y_position >= WINDOW_HEIGHT - 1)
    {
        const char* message = "You Lose! Press 'R' to play again.";

        int messageX = (WINDOW_WIDTH - 34) / 2;

        int messageY = WINDOW_HEIGHT / 2;


        Console::SetCursorPosition(messageX, messageY);

        Console::ForegroundColor(ConsoleColor::White);

        std::cout << message;
    }

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
    for (size_t i = 0; i < bricks.size(); i++)
    {
        if (bricks[i].Contains(ball.x_position, ball.y_position))
        {
            bricks[i].hits++;

            // TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
            if (bricks[i].hits == 1)
            {
                bricks[i].color = ConsoleColor::Yellow;
            }
            else if (bricks[i].hits == 2)
            {
                bricks[i].color = ConsoleColor::Red;
            }
            else if (bricks[i].hits >= 3)
            {
                bricks.erase(bricks.begin() + i);
            }

            ball.y_velocity *= -1;
            break;
        }
	}

	// TODO #6 - If no bricks remain, pause ball and display (render) victory text with R to reset
    if (bricks.empty())
    {
        ball.moving = false;
    }

	if (paddle.Contains(ball.x_position, ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display (render) defeat text with R to reset
    if (ball.y_position >= WINDOW_HEIGHT - 1)
    {
        ball.moving = false;
    }
}
