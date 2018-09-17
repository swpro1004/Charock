#pragma once
bool Dig_Check(POINT cs, Data &Player, HWND hWnd, LPARAM lParam, int &cps, Gem *Jewel);
int Click(POINT cs, Data Player, HWND hWnd, LPARAM lParam);
int Where(POINT cs, Data Player, HWND hWnd, LPARAM lParam);
int Click_Shop(POINT cs, Data Player, HWND hWnd, LPARAM lParam);
int Click_Room(POINT cs, Data &Player, HWND hWnd, LPARAM lParam, Gem *Jewel);
void Shop(POINT cs, Data &Player, HWND hwnd, LPARAM lParam, UINT &hTimer1);
void Click_Slot(POINT cs, Data &Player, HWND hWnd, LPARAM lParam, Gem *Jewel);