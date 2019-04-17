#include "stdafx.h"

static RECT rcClient;
static HDC hdc, hdc_;
static HBITMAP hbmp;
static PAINTSTRUCT ps;
static HBRUSH hBrush, oldBrush;
static HBITMAP hBitmap, oldBitmap;

RECT Bath_Resourse = { 384, 235, 193, 65 };
RECT Room_Resourse = { 384, 157, 193, 65 };
RECT BG1 = { 0, 0, 493, 1000 }; // 
RECT BG2_1 = { 1475, 0, 507, 1000 }; //
RECT BG2_2 = { 1988, 0, 509, 1000 }; //
RECT BG3_1 = { 2497, 0, 549, 1000 }; //
RECT BG3_2 = { 3046, 0, 549, 1000 }; //

void DrawMain(HWND hWnd, Data Player, HINSTANCE hInst, Gem Jewel[]) // 판 생성 - 배경 - 클리커 파트 - 상점 파트 - 보석장 파트 - 곡괭이 순으로 출력
{
	hdc_ = BeginPaint(hWnd, &ps);
	GetClientRect(hWnd, &rcClient);
	hbmp = CreateBitmap(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, 1, 32, NULL);
	hdc = CreateCompatibleDC(hdc_);
	SelectObject(hdc, hbmp);
	
	DrawBackground(Player, hInst);
	Draw1stPhase(Player, hInst);
	Draw2ndPhase(Player, hInst, Jewel);
	Draw3rdPhase(Player, hInst, Jewel);
	mineani(Player, hInst);
	BitBlt(hdc_, rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, hdc, 0, 0, SRCCOPY);
	DeleteObject(hbmp);
	DeleteDC(hdc);
	EndPaint(hWnd, &ps);
}

void DrawBackground(Data Player, HINSTANCE hInst) {
	RECT Print_01 = { 0, 0, 494, 1000 }; // 
	RECT Print_02 = { 494, 0, 511, 1000 }; //
	RECT Print_03 = { 1005, 0, 549, 1000 }; //

	BG1 = { 0, 0 + (1000 * (Player.displayRock01 + Player.displayRock02)), 489, 1000 }; // 

	DrawBG(hInst, Print_01, BG1);
	if (Player.Clicked_2nd != 1) DrawBG(hInst, Print_02, BG2_1);
	else DrawBG(hInst, Print_02, BG2_2);
	if (Player.Clicked_3rd == 1) DrawBG(hInst, Print_03, BG3_1);
	else DrawBG(hInst, Print_03, BG3_2);
}

void mineani(Data Player, HINSTANCE hInst) {
	RECT Print_[12] = {
	{ 318, 250, 34 , 31 }, { 353, 285, 34 , 31 },
	{ 373, 325, 34 , 31 }, { 385, 365, 34 , 31 },
	{ 388, 405, 34 , 31 }, { 383, 445, 34 , 31 },
	{ 177, 250, 34 , 31 },{ 145, 285, 34 , 31 },
	{ 125, 325, 34 , 31 },{ 110, 365, 34 , 31 },
	{ 110, 405, 34 , 31 },{ 115, 445, 34 , 31 } };
	int isEnable, isReverse, isIron;
	for (int i = 0; i < Player.amountP1+ Player.amountP2; i++) {
		if (Player.currentEnablePickaxe) isEnable = 1;
		else isEnable = 0;
		if (i >= 6) isReverse = 1;
		else isReverse = 0;
		if (Player.displayPickaxe[i] == 2) isIron = 1;
		else isIron = 0;
		Drawani(hInst, Print_[i], isEnable, isReverse, isIron);
	}
}

void Draw1stPhase(Data Player, HINSTANCE hInst) {
	//Text
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "LVDC Game Over 2");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	RECT gold = { 80, 20, 290, 57 };
	RECT cSP = { 80, 73, 315, 116 };
	RECT time_ = { 10, 130, 64, 150 };
	RECT rHP = { 75, 250, 425, 300 };
	RECT mNotice = { 35, 550, 465, 600 };

	char HP[10], gld[10], Msp[10], sp[10], time[10];
	itoa(Player.rockHP, HP, 10);
	itoa(Player.amountGold, gld, 10);
	itoa(Player.maxSP, Msp, 10);
	itoa(Player.currentSP, sp, 10);
	itoa(Player.timeCount, time, 10);
	strcat(sp, " / ");
	strcat(sp, Msp);
	DrawText(hdc, gld, -1, &gold, DT_LEFT);
	DrawText(hdc, sp, -1, &cSP, DT_LEFT);
	DrawText(hdc, HP, -1, &mNotice, DT_CENTER);

	myFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "LVDC Game Over 2");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	if (Player.currentSP < 20) DrawText(hdc, time, -1, &time_, DT_CENTER);

	myFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "10X10");
	oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	RECT Print_Message[6] = { { 45, 775, 450, 805 },{ 45, 810, 450, 840 },{ 45, 845, 450, 875 },{ 45, 880, 450, 910 },{ 45, 915, 450, 945 },{ 45, 950, 450, 980 } } ;
	for (int i = 0; i < 6; i++) DrawText(hdc, Player.print_data[5-i], -1, &Print_Message[i], DT_LEFT);
	DeleteObject(SelectObject(hdc, oldFont));
}

void Draw2ndPhase(Data Player, HINSTANCE hInst, Gem Jewel[]) {
	if (Player.Clicked_2nd == 1) {
		
		RECT Print_01 = { 560, 245, 120, 120 }; // 
		RECT Print_02 = { 820, 245, 120, 120 }; // 
		RECT Print_03 = { 690, 370, 120, 120 }; //
		RECT Print_04 = { 560, 495, 120, 120 }; //
		RECT Print_05 = { 820, 495, 120, 120 }; //

		if (Jewel[0].amountGem >= 1) DrawGem(hInst, Print_01, 0);
		if (Jewel[1].amountGem >= 1) DrawGem(hInst, Print_02, 1);
		if (Jewel[2].amountGem >= 1) DrawGem(hInst, Print_03, 2);
		if (Jewel[3].amountGem >= 1) DrawGem(hInst, Print_04, 3);
		if (Jewel[4].amountGem >= 1) DrawGem(hInst, Print_05, 4);
		HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "10X10");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		RECT NOTICE = { 580, 707, 930, 765 };

		DrawText(hdc, "지금까지 모은 보석의 갯수!", -1, &NOTICE, DT_CENTER);
		char amountGem[5][3];
		for (int i = 0; i < 5; i++) itoa(Jewel[i].amountGem, amountGem[i], 10);

		RECT displayGem[5] = { { 530, 800, 635, 860 },{ 695, 800, 790, 860 },{ 870, 800, 945, 860 },{ 610, 910, 710, 975 },{ 800, 905, 890, 975 } };

		for (int i = 0; i < 5; i++) DrawText(hdc, amountGem[i], -1, &displayGem[i], DT_CENTER);
		
	}
	else {
		//Text
		HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "LVDC Game Over 2");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
		SetTextColor(hdc, RGB(0, 0, 0));

		char P1[10], P2[10];
		itoa(Player.amountP1, P1, 10);
		itoa(Player.amountP2, P2, 10);

		RECT aItem1 = { 650, 790, 750, 830 };
		RECT aItem2 = { 880, 790, 960, 830 };

		DrawText(hdc, P1, -1, &aItem1, DT_LEFT);
		DrawText(hdc, P2, -1, &aItem2, DT_LEFT);

		DeleteObject(SelectObject(hdc, oldFont));
	}
}

void Draw3rdPhase(Data Player, HINSTANCE hInst, Gem *Jewel) {
	RECT Print_01 = { 1020, 920, 193, 65 }; //
	RECT Print_02 = { 1350, 918, 193, 65 }; //
	RECT Print_03 = { 1080, 400, 400, 400 }; //

	DrawEntity(hInst, Print_01, Room_Resourse, 1);
	DrawEntity(hInst, Print_02, Bath_Resourse, 1);
	if (Player.Clicked_Gem != 5 && Jewel[Player.Clicked_Gem].amountGem >= 1) DrawGem(hInst, Print_03, Player.Clicked_Gem);
	DrawEntity_(hInst, Player.Clicked_3rd);
	if (Player.Clicked_3rd == 2) DrawEffect(hInst, Player.BathEffect);

	HFONT myFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "LVDC Game Over 2");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	RECT HP_ = { 1115, 875, 1445, 920 };

	char HP[10];
	itoa(Jewel[Player.Clicked_Gem].gemExp, HP, 10);
	DrawText(hdc, HP, -1, &HP_, DT_CENTER);
	DeleteObject(SelectObject(hdc, oldFont));
}

void DrawEntity(HINSTANCE hInst, RECT print, RECT Resouese, int RGBType) {
	static int type; if (RGBType == 1) type = 255; else type = 0;

	static HDC MemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(Layer));
	oldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
	TransparentBlt(hdc, print.left, print.top, print.right, print.bottom, MemDC, Resouese.left, Resouese.top, Resouese.right, Resouese.bottom, RGB(255, type, 255));
	DeleteObject(SelectObject(MemDC, oldBitmap)); 
}

void DrawBG(HINSTANCE hInst, RECT print, RECT Resouese) {
	static HDC MemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(BG));
	oldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
	TransparentBlt(hdc, print.left, print.top, print.right, print.bottom, MemDC, Resouese.left, Resouese.top, Resouese.right, Resouese.bottom, NULL);
	DeleteObject(SelectObject(MemDC, oldBitmap));
}

void DrawGem(HINSTANCE hInst, RECT print, int Gem_Type) {
	static HDC MemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(GEM));
	oldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
	TransparentBlt(hdc, print.left, print.top, print.right, print.bottom, MemDC, 0+(Gem_Type*500), 0, 500, 500, RGB(255, 255, 255));
	DeleteObject(SelectObject(MemDC, oldBitmap));
}

void DrawMessageBox(HINSTANCE hInst, RECT print, RECT Resouese) {
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "10X10");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
}

void Drawani(HINSTANCE hInst, RECT print, int isEnable, int isReverse, int isIron) {
	static HDC MemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(anime));
	oldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
	TransparentBlt(hdc, print.left, print.top, print.right, print.bottom, MemDC, 0+(isEnable*34) + (isIron * 68), 0 + (isReverse * 31), 34, 31, RGB(255, 255, 255));
	DeleteObject(SelectObject(MemDC, oldBitmap));
}

void DrawEffect(HINSTANCE hInst, int isEnable) {
	static HDC MemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(BATHEFFECT));
	oldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
	TransparentBlt(hdc, 1037, 565, 473, 87, MemDC, 0, 0 + (isEnable * 87), 473, 86, RGB(255, 255, 255));
	DeleteObject(SelectObject(MemDC, oldBitmap));
}

void DrawEntity_(HINSTANCE hInst, int EntityType) {
	static HDC MemDC = CreateCompatibleDC(hdc);
	switch (EntityType) {
	case 2:
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(BATH));
		oldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
		TransparentBlt(hdc, 1033, 322, 485, 550, MemDC, 0, 0, 488, 593, RGB(255, 255, 255));
		break;
	case 1:
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(ROOM));
		oldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);
		TransparentBlt(hdc, 1055, 660, 445, 213, MemDC, 0, 0, 445, 213, RGB(255, 255, 255));
		break;
	}
	DeleteObject(SelectObject(MemDC, oldBitmap));
}