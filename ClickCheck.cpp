#include "stdafx.h"
char printdata_[100];
bool Dig_Check(POINT cs, Data &Player, HWND hWnd, LPARAM lParam, int &cps, Gem *Jewel){
	if (cs.x >= 75 && cs.x <= 425 && cs.y >= 275 && cs.y <= 625) {
		if (Player.currentSP > 0) {
			Player.rockHP--;
			HPCheck(Player, Jewel);
		}
		cps++;
		return TRUE;
	}
	else return FALSE;
}

int Click(POINT cs, Data Player, HWND hWnd, LPARAM lParam)
{
	if (cs.x >= 666 && cs.x <= 910 && cs.y >= 55 && cs.y <= 130) return 1;
	else if (cs.x >= 500 && cs.x <= 665 && cs.y >= 55 && cs.y <= 130) return 2;
	else return Player.Clicked_2nd;
}

int Where(POINT cs, Data Player, HWND hWnd, LPARAM lParam)
{
	if (cs.x >= 0 && cs.x <= 494) return 1;
	else if (cs.x >= 495 && cs.x <= 1005) return 2;
	else if (cs.x >= 1006 && cs.x <= 1554) return 3;
	else return 0;
}

int Click_Shop(POINT cs, Data Player, HWND hWnd, LPARAM lParam)
{
	if (cs.x >= 815 && cs.x <= 980 && cs.y >= 245 && cs.y <= 315) return 1; 
	else if (cs.x >= 815 && cs.x <= 980 && cs.y >= 420 && cs.y <= 490) return 2;
	else if (cs.x >= 815 && cs.x <= 980 && cs.y >= 585 && cs.y <= 655) return 3;
	else return 0;
}

int Click_Room(POINT cs, Data &Player, HWND hWnd, LPARAM lParam, Gem *Jewel)
{
	if (cs.x >= 1020 && cs.x <= 1214 && cs.y >= 919 && cs.y <= 984) Player.Clicked_3rd = 1;
	else if (cs.x >= 1350 && cs.x <= 1544 && cs.y >= 919 && cs.y <= 984) Player.Clicked_3rd = 2;
	else if (cs.x >= 1080 && cs.x <= 1480 && cs.y >= 400 && cs.y <= 800) return 3;
	return 0;
}

void Click_Slot(POINT cs, Data &Player, HWND hWnd, LPARAM lParam, Gem *Jewel)
{
	if (cs.x >= 560 && cs.y >= 245 && cs.x <= 680 && cs.y <= 365) Player.Clicked_Gem = 0;
	else if (cs.x >= 820 && cs.y >= 245 && cs.x <= 940 && cs.y <= 365)  Player.Clicked_Gem = 1;
	else if (cs.x >= 690 && cs.y >= 370 && cs.x <= 810 && cs.y <= 490) Player.Clicked_Gem = 2;
	else if (cs.x >= 560 && cs.y >= 495 && cs.x <= 680 && cs.y <= 615) Player.Clicked_Gem = 3;
	else if (cs.x >= 820 && cs.y >= 495 && cs.x <= 940 && cs.y <= 615) Player.Clicked_Gem = 4;
	else if (cs.x >= 560 && cs.y >= 370 && cs.x <= 680 && cs.y <= 490) {
		if (Jewel[0].amountGem >= 1 && Jewel[1].amountGem >= 1 && Jewel[2].amountGem >= 1
			&& Jewel[0].gemExp >= 200 && Jewel[1].gemExp >= 200 && Jewel[2].gemExp >= 200) {
			Jewel[0].amountGem--;
			Jewel[1].amountGem--;
			Jewel[2].amountGem--;
			Jewel[0].gemExp = 0;
			Jewel[1].gemExp = 0;
			Jewel[2].gemExp = 0;
			Jewel[3].amountGem++;
			strcpy(printdata_, "Çª¸¥ ºû »ð°ãµ¹À» È¹µæÇß´Ù!");
			newQ(printdata_, Player);
		}
	}
	else if (cs.x >= 820 && cs.y >= 370 && cs.x <= 940 && cs.y <= 490) {
		if (Jewel[3].gemExp >= 1000) {
			Jewel[3].gemExp = 0;
			Jewel[3].amountGem--;
			Jewel[4].amountGem++;
			strcpy(printdata_, "¹«Áö °³°°Àº µ¹À» È¹µæÇß´Ù!");
			newQ(printdata_, Player);
		}
	}
}

void Shop(POINT cs, Data &Player, HWND hwnd, LPARAM lParam, UINT &hTimer1){
	switch (Click_Shop(cs, Player, hwnd, lParam)) {
	case 1:
		if (Player.amountP1 + Player.amountP2 < 12) {
			if (Player.amountGold >= 150) {
				Player.amountGold -= 150;
				Player.displayPickaxe[Player.amountP1 + Player.amountP2] = 1;
				Player.amountP1++;
				strcpy(printdata_, "Àßµå´Â µ¹ °î±ªÀÌ¸¦ È¹µæÇß´Ù!");
				newQ(printdata_, Player);
			}
		}
		break;
	case 2:
		if (Player.amountP1 + Player.amountP2 < 12) {
			if (Player.amountGold >= 200) {
				Player.amountGold -= 200;
				Player.displayPickaxe[Player.amountP1 + Player.amountP2] = 2;
				Player.amountP2++;
				strcpy(printdata_, "Â¼´Â Ã¶ °î±ªÀÌ¸¦ È¹µæÇß´Ù!");
				newQ(printdata_, Player);
			}
		}
		else if (Player.amountP1 >= 1) {
			static bool isChanged;
			if (Player.amountGold >= 200) {
				Player.amountGold -= 200;
				Player.amountP2++;
				Player.amountP1--;
				strcpy(printdata_, "Â¼´Â Ã¶ °î±ªÀÌ¸¦ È¹µæÇß´Ù!");
				newQ(printdata_, Player);
				isChanged = TRUE;
				for (int i = 0; isChanged; i++) {
					if (Player.displayPickaxe[i] == 1) {
						Player.displayPickaxe[i] = 2;
						isChanged = FALSE;
					}
				}
			}
		}
		break;
	case 3:
		if (Player.maxSP != Player.currentSP) {
			if (Player.amountGold >= 250) {
				Player.amountGold -= 250;
				Player.currentSP += Player.maxSP / 2;
				if (Player.currentSP >= Player.maxSP) {
					Player.currentSP = Player.maxSP;
					Player.timeCount = 60 + 2 * Player.clearRockCount;
				}
				strcpy(printdata_, "±â¿îÆÞÆÞ ¹ø°³¹°¾àÀ» È¹µæÇß´Ù!");
				newQ(printdata_, Player);
			}
		}
		break;
	}

}