#include "stdafx.h"
#include "Charock_.h"

HINSTANCE g_hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char* lpszClass = "ĳ�� ĳ�� ü����";
POINT cs;
WNDCLASS WndClass;
static Data Player;
static Gem Jewel[5];
static int cps = 0;
HWND hWnd;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	srand(time(NULL));
	MSG Message;
	static char fontDirectory[MAX_PATH];
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
	WndClass.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_CHAROCK_));
	WndClass.hInstance = g_hInst;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1571, 1039, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	GetCurrentDirectory(MAX_PATH, fontDirectory);
	strcat(fontDirectory, "\\Fonts\\10X10.ttf");
	AddFontResource(fontDirectory);

	GetCurrentDirectory(MAX_PATH, fontDirectory);
	strcat(fontDirectory, "\\Fonts\\LVDCGO__.TTF");
	AddFontResource(fontDirectory);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int random_, Slot_ = 0, WhereisCursor = 1;
	static UINT hTimer1, hTimer2, hTimer3, hTimer4;
	switch (message)
	{
	case WM_CREATE:
		if (!loadData(Player, Jewel)) {
			Player = { 2, 1, 5, 0, 50, 50, 0, 0, 20, 20, 0, 0, 0, 0, 60,{ 0, },{ " ", }, 0, 0 };
			Jewel[0] = { "��Ÿ�� ����", 0, 0 };
			Jewel[1] = { "�Ķ����̾�", 0, 0 };
			Jewel[2] = { "������ ��", 0, 0 };
			Jewel[3] = { "Ǫ�� �� ��㵹", 0, 0 };
			Jewel[4] = { "���� ������ ��", 0, 0 };
		}
		hTimer1 = timeSetEvent(1000, 100, (LPTIMECALLBACK)TimerProc, 1, TIME_PERIODIC);
		hTimer2 = timeSetEvent(1000, 100, (LPTIMECALLBACK)TimerProc, 2, TIME_PERIODIC);
		hTimer3 = timeSetEvent(5, 100, (LPTIMECALLBACK)TimerProc, 3, TIME_PERIODIC);
		hTimer4 = timeSetEvent(30000, 100, (LPTIMECALLBACK)TimerProc, 4, TIME_PERIODIC);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_ABOUT:
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
		break;
	case WM_PAINT:
		DrawMain(hwnd, Player, g_hInst, Jewel);
		break;

	case WM_MOUSEMOVE:
		cs = { LOWORD(lParam), HIWORD(lParam) };
		Player.Clicked_2nd = Click(cs, Player, hwnd, lParam);
		switch (Where(cs, Player, hwnd, lParam)) {
		case 1:
			SetCursor(LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_DIG)));
			break;
		case 3:
			SetCursor(LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_HAND)));
			break;
		}
		break;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 1571;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 1039;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 1571;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 1039;
		break;

	case WM_LBUTTONDOWN:
		cs = { LOWORD(lParam), HIWORD(lParam) };
		Dig_Check(cs, Player, hwnd, lParam, cps, Jewel);
		WhereisCursor = Where(cs, Player, hwnd, lParam);
		switch (Player.Clicked_2nd) {
		case 1:
			Click_Slot(cs, Player, hwnd, lParam, Jewel);
			break;
		case 2:
			Shop(cs, Player, hwnd, lParam, hTimer1);
			break;
		}
		if (Click_Room(cs, Player, hwnd, lParam, Jewel) == 3) {
			if (Player.Clicked_Gem != 5 && Jewel[Player.Clicked_Gem].amountGem >= 1)
			{
				Jewel[Player.Clicked_Gem].gemExp++;
				if (Player.Clicked_3rd == 2) Player.BathEffect = !Player.BathEffect;
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_LBUTTONUP:
		WhereisCursor = Where(cs, Player, hwnd, lParam);
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_DESTROY:
		saveData(Player, Jewel);

		static char fontDirectory[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, fontDirectory);
		strcat(fontDirectory, "\\Fonts\\10X10.ttf");
		RemoveFontResource(fontDirectory);

		GetCurrentDirectory(MAX_PATH, fontDirectory);
		strcat(fontDirectory, "\\Fonts\\LVDCGO__.TTF");
		RemoveFontResource(fontDirectory);

		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void CALLBACK TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	switch (dwUser) {
	case 2:
		AutoCharge(Player);
		cpsCheck(cps, hWnd);
		break;
	case 1:
		AutoMining(Player);
		break;
	case 3:
		HPCheck(Player, Jewel);
		break;
	case 4:
		saveData(Player, Jewel);
		break;
	}
	InvalidateRect(hWnd, NULL, FALSE);
}