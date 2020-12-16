#include <windows.h>
#include "PuzzleGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int show)
{
	PuzzleGame puzzle;
	puzzle.create(hInstance, 800, 600, 100, true);

	return 0;
}