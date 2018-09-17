#include "stdafx.h"
char printdata[100];
void AutoMining(Data &Player)
{
	static int Temp = 1;
	if (Player.amountP1 + Player.amountP2 > 0) {
		if (Player.currentSP > 0) {
			Player.rockHP -= (Player.amountP1 + (Player.amountP2 * 2));
			if (Temp == 1) {
				Player.currentEnablePickaxe = 1;
				Temp--;
			}
			else {
				Player.currentEnablePickaxe = 0;
				Temp++;
			}
		}
	}
}

void AutoCharge(Data &Player)
{
	if (Player.currentSP < Player.maxSP) {
		Player.timeCount--;
		if (Player.timeCount == 0) {
			Player.currentSP += 2;
			if (Player.currentSP >= Player.maxSP) Player.currentSP = Player.maxSP;
			Player.timeCount = 60 + 2 * Player.clearRockCount;
			strcpy(printdata, "SP�� ȸ���ߴ�!");
			newQ(printdata, Player);
		}
	}
}

void cpsCheck(int &cps, HWND hWnd)
{
	if (cps >= 30) MessageBox(hWnd, "����� ��ǻ�Ϳ� �ʴ� 30�� �̻� Ŭ���Ǵ� ���̷����� �ֽ��ϴ�!", "Warning!", MB_OK | MB_ICONHAND);
	cps = 0;
}

void HPCheck(Data &Player, Gem *Jewel)
{
	if (Player.rockHP <= Player.MaxrockHP / 3) Player.displayRock01 = 1;
	if (Player.rockHP <= (Player.MaxrockHP / 3) * 2) Player.displayRock02 = 1;
	if (Player.rockHP <= 0) {
		static int getGold;
		char gold_[10];
		getGold = ((1 + rand() % 7) * 10);
		Player.displayRock01 = 0;
		Player.displayRock02 = 0;
		Player.clearRockCount++;
		Player.currentSP--;
		Player.amountGold += getGold;
		Player.MaxrockHP = 50 + 30 * Player.clearRockCount * 0.3;
		Player.rockHP = Player.MaxrockHP;

		itoa(getGold, gold_, 10);
		strcpy(printdata, gold_);
		strcat(printdata, " ��带 ȹ���ߴ�!");
		newQ(printdata, Player);

		switch (1 + rand() % 100) {
		case 1: case 2: case 3: case 4:
			Jewel[0].amountGem++;
			strcpy(printdata, "��Ÿ�� ������ ȹ���ߴ�!");
			newQ(printdata, Player);
			break;
		case 5: case 6: case 7: case 8:
			Jewel[1].amountGem++;
			strcpy(printdata, "�غ��� ȹ���ߴ�!");
			newQ(printdata, Player);
			break;
		case 9: case 10: case 11: case 12:
			Jewel[2].amountGem++;
			strcpy(printdata, "����Ÿ�� ������ ȹ���ߴ�!");
			newQ(printdata, Player);
			break;
		}
	}
}
