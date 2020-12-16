#pragma once
#include "EasyGraphics.h"
#include <random>

class PuzzleGame :
	public EasyGraphics
{
public:
	PuzzleGame();
	~PuzzleGame();

	//none=0, up=1, right=2, left=3, down=4
	enum direction { none, up, right, left, down };

	struct tile
	{
		std::wstring filepath;
		direction anim_direction = { none };
		int start_time = { 0 };
	};

	tile arr[5][5] = { {tile{L"assets\\AA.bmp"},tile{L"assets\\AB.bmp"},tile{L"assets\\AC.bmp"}, tile{L"assets\\AD.bmp"},tile{L"assets\\AE.bmp"}},
					   {tile{L"assets\\BA.bmp"},tile{L"assets\\BB.bmp"},tile{L"assets\\BC.bmp"}, tile{L"assets\\BD.bmp"},tile{L"assets\\BE.bmp"}},
					   {tile{L"assets\\CA.bmp"},tile{L"assets\\CB.bmp"},tile{L"assets\\CC.bmp"}, tile{L"assets\\CD.bmp"},tile{L"assets\\CE.bmp"}},
					   {tile{L"assets\\DA.bmp"},tile{L"assets\\DB.bmp"},tile{L"assets\\DC.bmp"}, tile{L"assets\\DD.bmp"},tile{L"assets\\DE.bmp"}},
					   {tile{L"assets\\EA.bmp"},tile{L"assets\\EB.bmp"},tile{L"assets\\EC.bmp"}, tile{L"assets\\ED.bmp"},tile{L"XX"}}};

	std::wstring solution[5][5] = {{L"assets\\AA.bmp",L"assets\\AB.bmp",L"assets\\AC.bmp",L"assets\\AD.bmp",L"assets\\AE.bmp"},
		                           {L"assets\\BA.bmp",L"assets\\BB.bmp",L"assets\\BC.bmp",L"assets\\BD.bmp",L"assets\\BE.bmp"},
		                           {L"assets\\CA.bmp",L"assets\\CB.bmp",L"assets\\CC.bmp",L"assets\\CD.bmp",L"assets\\CE.bmp"},
		                           {L"assets\\DA.bmp",L"assets\\DB.bmp",L"assets\\DC.bmp",L"assets\\DD.bmp",L"assets\\DE.bmp"},
		                           {L"assets\\EA.bmp",L"assets\\EB.bmp",L"assets\\EC.bmp",L"assets\\ED.bmp",L"XX"}};
	
	bool solved;
	bool animate = false;
	UINT timer_id = 1;
	UINT anim_id = 2;
	UINT time;
	UINT moves;

	const double anim_time = 250.0;

	void onDraw() override;
	void onLButtonDown(UINT nFlags, int x, int y) override;
	void onTimer(UINT nIDEvent) override;
	void drawTile(int x, int y);
	void swapUp(int pos_x, int pos_y, bool animation = true);
	void swapDown(int pos_x, int pos_y, bool animation = true);
	void swapLeft(int pos_x, int pos_y, bool animation = true);
	void swapRight(int pos_x, int pos_y, bool animation = true);
	bool isSolved() const;
	void start();
};

