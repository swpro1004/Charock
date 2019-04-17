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
			strcpy(printdata, "SP를 회복했다!");
			newQ(printdata, Player);
		}
	}
}

void cpsCheck(int &cps, HWND hWnd)
{ // 1초마다 클릭 횟수 검사
	if (cps >= 30) MessageBox(hWnd, "당신의 컴퓨터에 초당 30초 이상 클릭되는 바이러스가 있습니다!", "Warning!", MB_OK | MB_ICONHAND);
	cps = 0;
}

void HPCheck(Data &Player, Gem *Jewel)
{
	if (Player.rockHP <= Player.MaxrockHP / 3) Player.displayRock01 = 1; // 1/3 완료시
	if (Player.rockHP <= (Player.MaxrockHP / 3) * 2) Player.displayRock02 = 1; // 2/3 완료시
	if (Player.rockHP <= 0) { // 모두 완료시
		static int getGold;
		char gold_[10];
		getGold = ((1 + rand() % 7) * 10); // 골드 랜덤 획득
		Player.displayRock01 = 0;
		Player.displayRock02 = 0;
		Player.clearRockCount++;
		Player.currentSP--;
		Player.amountGold += getGold;
		Player.MaxrockHP = 30 + 9 * Player.clearRockCount; // 부순 돌 갯수에 비례하여 체력 증가
		Player.rockHP = Player.MaxrockHP;

		itoa(getGold, gold_, 10);
		strcpy(printdata, gold_);
		strcat(printdata, " 골드를 획득했다!");
		newQ(printdata, Player);

		switch (1 + rand() % 100) {
		case 1: case 2: case 3: case 4:
			Jewel[0].amountGem++;
			strcpy(printdata, "비타민 씨돌을 획득했다!");
			newQ(printdata, Player);
			break;
		case 5: case 6: case 7: case 8:
			Jewel[1].amountGem++;
			strcpy(printdata, "솜보라를 획득했다!");
			newQ(printdata, Player);
			break;
		case 9: case 10: case 11: case 12:
			Jewel[2].amountGem++;
			strcpy(printdata, "마젠타의 눈물을 획득했다!");
			newQ(printdata, Player);
			break;
		}
	}
}
