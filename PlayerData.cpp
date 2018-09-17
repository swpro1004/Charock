#include "stdafx.h"

bool saveData(Data &Player, Gem*Jewel)
{
	FILE *data;
	data = fopen("data.sav", "w");
	if (data == NULL) return FALSE;
	fprintf(data,
		"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",
		Player.Clicked_2nd,
		Player.Clicked_3rd,
		Player.Clicked_Gem,
		Player.itemSelect,
		Player.MaxrockHP,
		Player.rockHP,
		Player.clearRockCount,
		Player.amountGold,
		Player.maxSP,
		Player.currentSP,
		Player.amountP1,
		Player.amountP2,
		Player.displayRock01,
		Player.displayRock02,
		Player.timeCount,
		Player.currentEnablePickaxe,
		Player.BathEffect);
	
	for (int i = 0; i < 13; i++) fprintf(data, "%d ", Player.displayPickaxe[i]);
	for (int i = 0; i < 5; i++) fprintf(data, "%d %d ", Jewel[i].amountGem, Jewel[i].gemExp);

	fclose(data);

	return TRUE;
}

bool loadData(Data &Player, Gem *Jewel)
{
	FILE *data;
	data = fopen("data.sav", "r");
	if (data == NULL) return FALSE;
	fscanf(data,
		"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&Player.Clicked_2nd,
		&Player.Clicked_3rd,
		&Player.Clicked_Gem,
		&Player.itemSelect,
		&Player.MaxrockHP,
		&Player.rockHP,
		&Player.clearRockCount,
		&Player.amountGold,
		&Player.maxSP,
		&Player.currentSP,
		&Player.amountP1,
		&Player.amountP2,
		&Player.displayRock01,
		&Player.displayRock02,
		&Player.timeCount,
		&Player.currentEnablePickaxe,
		&Player.BathEffect);

	for (int i = 0; i < 13; i++) fscanf(data, "%d", &Player.displayPickaxe[i]);
	for (int i = 0; i < 5; i++) fprintf(data, "%d %d", &Jewel[i].amountGem, &Jewel[i].gemExp);

	fclose(data);

	return TRUE;
}
