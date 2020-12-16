#include "PuzzleGame.h"
#include <random>

PuzzleGame::PuzzleGame()
{
	setImmediateDrawMode(false);
	time = 0;
	solved = true;
	moves = 0;
}

PuzzleGame::~PuzzleGame()
= default;

void PuzzleGame::onDraw()
{
	clearScreen(WHITE);
	setBackColour(GREY);
	setPenColour(BLACK,2);
	setFont(20, L"Tahoma");
	setTextColour(BLACK);
  
    drawRectangle(265, 90, 270, 270, true);

	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			drawTile(i, j);
		}
	}

    drawRectangle(315, 400, 170, 50, true);

	if(solved)
	{
		drawText(L"Start", 365, 405);
		drawText(L"Well done!", 550, 180);
	}
	else 
	{ 
		drawText(L"Restart", 365, 405);
	}

	std::string time_txt = "Time:" + std::to_string(time / 100.0);
	std::string moves_txt = "Moves:" + std::to_string(moves);
	drawText(time_txt.c_str(), 550, 100);
	drawText(moves_txt.c_str(), 550, 140);

	EasyGraphics::onDraw();
}

void PuzzleGame::onLButtonDown(UINT nFlags, const int x, const int y)
{
	if(x > 315 && x < 485 && y > 400 && y < 450)
	{
		start();
	}
	else if (!animate && x > 275 && x < 525 && y > 100 && y < 350)
	{
		const int pos_x = (x - 275) / 50;
		const int pos_y = (y - 100) / 50;

		if (pos_x < 4 && arr[pos_y][pos_x + 1].filepath == L"XX")
		{
			swapLeft(pos_x, pos_y);
		}
		else if (pos_x > 0 && arr[pos_y][pos_x - 1].filepath == L"XX")
		{
			swapRight(pos_x, pos_y);
		}
		else if (pos_y < 4 && arr[pos_y + 1][pos_x].filepath == L"XX")
		{
			swapDown(pos_x, pos_y);
		}
		else if (pos_y > 0 && arr[pos_y - 1][pos_x].filepath == L"XX")
		{
			swapUp(pos_x, pos_y);
		}
	}
	solved = isSolved();
	onDraw();
}

void PuzzleGame::swapUp(const int pos_x, const int pos_y, const bool animation)
{
	arr[pos_y - 1][pos_x] = arr[pos_y][pos_x];
	arr[pos_y][pos_x] = tile{L"XX"};
	if (animation) {
		moves++;
		animate = true;
		arr[pos_y - 1][pos_x].anim_direction = up;
		arr[pos_y - 1][pos_x].start_time = GetTickCount();
	}
}

void PuzzleGame::swapDown(const int pos_x, const int pos_y, const bool animation)
{
	arr[pos_y + 1][pos_x] = arr[pos_y][pos_x];
	arr[pos_y][pos_x] = tile{ L"XX" };
	if (animation) {
		moves++;
		animate = true;
		arr[pos_y + 1][pos_x].anim_direction = down;
		arr[pos_y + 1][pos_x].start_time = GetTickCount();
	}
}

void PuzzleGame::swapLeft(const int pos_x, const int pos_y, const bool animation)
{
	arr[pos_y][pos_x + 1] = arr[pos_y][pos_x];
	arr[pos_y][pos_x] = tile{ L"XX" };
	if (animation) {
		moves++;
		animate = true;
		arr[pos_y][pos_x + 1].anim_direction = left;
		arr[pos_y][pos_x + 1].start_time = GetTickCount();
	}
}

void PuzzleGame::swapRight(const int pos_x, const int pos_y, const bool animation)
{
	arr[pos_y][pos_x - 1] = arr[pos_y][pos_x];
	arr[pos_y][pos_x] = tile{ L"XX" };
	if (animation) {
		moves++;
		animate = true;
		arr[pos_y][pos_x - 1].anim_direction = right;
		arr[pos_y][pos_x - 1].start_time = GetTickCount();
	}
}


void PuzzleGame::onTimer(UINT nIDEvent)
{
	if (nIDEvent == timer_id)
	{
		time++;
		onDraw();
	}
}

void PuzzleGame::drawTile(int x, int y)
{
	tile current_tile = arr[y][x];
	int x_pos = 275 + (50 * x);
	int y_pos = 100 + (50 * y);

	if (current_tile.anim_direction != none)
	{
		const DWORD diff = GetTickCount() - current_tile.start_time;
		if (diff > anim_time)
		{
			current_tile.anim_direction = none;
			animate = false;
			if (solved)
			{
				killTimer(timer_id);
			}
		}
		else
		{
			int move = 50;
			if (diff > 0) {
				move -= 50 * (diff / anim_time);
			}
			switch (current_tile.anim_direction) {
			case up:
				y_pos += move;
				break;
			case right:
				x_pos += move;
				break;
			case left:
				x_pos -= move;
				break;
			case down:
				y_pos -= move;
				break;
			case none: break;
			default:;
			}
		}
	}

	drawBitmap(current_tile.filepath.c_str(), x_pos, y_pos, 49, 49);
}

void PuzzleGame::start()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[j][i] = tile{ solution[j][i] };
		}
	}
	animate = false;

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	const std::uniform_int_distribution<> distribution(0, 3);

	int blank_x = 4;
	int blank_y = 4;

	for(int i = 0; i < 200; i++)
	{
		const int rand = distribution(eng);
		switch(rand)
		{
		case 0:
			if (blank_x - 1 >= 0) {
				blank_x -= 1;
				swapLeft(blank_x, blank_y,false);	
			}
			break;
		case 1:
			if (blank_x + 1 <= 4) {
				blank_x += 1;
				swapRight(blank_x, blank_y, false);
			}
			break;
		case 2:
			if (blank_y - 1 >= 0) {
				blank_y -= 1;
				swapDown(blank_x, blank_y, false);
			}
			break;
		case 3:
			if (blank_y + 1 <= 4) {
				blank_y += 1;
				swapUp(blank_x, blank_y, false);
			}
			break;
		default:
			break;
		}
	}

	time = 0;
	moves = 0;
	setTimer(timer_id, 10);
	onDraw();
}

bool PuzzleGame::isSolved() const
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			if (arr[j][i].filepath != solution[j][i])
			{
				return false;
			}
		}
	}
	return true;
}