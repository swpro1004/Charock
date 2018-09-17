#pragma once
void DrawMain(HWND hWnd, Data Player, HINSTANCE hInst, Gem Jewel[]);
void DrawBackground(Data Player, HINSTANCE hInst);
void Draw1stPhase(Data Player, HINSTANCE hInst);
void Draw2ndPhase(Data Player, HINSTANCE hInst, Gem Jewel[]);
void Draw3rdPhase(Data Player, HINSTANCE hInst, Gem *Jewel);
void DrawEntity(HINSTANCE hInst, RECT print, RECT Resouese, int RGBType);
void DrawBG(HINSTANCE hInst, RECT print, RECT Resouese);
void DrawGem(HINSTANCE hInst, RECT print, int Gem_Type);
void mineani(Data Player, HINSTANCE hInst);
void Drawani(HINSTANCE hInst, RECT print, int isEnable, int isReverse, int isIron);
void DrawEffect(HINSTANCE hInst, int isEnable);
void DrawEntity_(HINSTANCE hInst, int EntityType);