#pragma once
struct Data {
	int Clicked_2nd;
	int Clicked_3rd;
	int Clicked_Gem;
	int itemSelect;
	int MaxrockHP;
	int rockHP;
	int clearRockCount;
	int amountGold;
	int maxSP;
	int currentSP;
	int amountP1;
	int amountP2;
	int displayRock01;
	int displayRock02;
	int timeCount;
	int displayPickaxe[13];
	char print_data[6][100];
	int currentEnablePickaxe;
	int BathEffect;
};

struct Gem {
	char* GemName;
	int amountGem;
	int gemExp;
};

bool saveData(Data &Player, Gem *Jewel);
bool loadData(Data &Player, Gem *Jewel);