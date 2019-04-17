#include "stdafx.h"
int i = 6;

void delQ(Data &Player) {
	strcpy(Player.print_data[0], "0"); // 첫 데이터 삭제
	for (int j = 1; j < i; j++) {
		strcpy(Player.print_data[j - 1], Player.print_data[j]); // 데이터 한칸씩 이동
	}
	strcpy(Player.print_data[5], ""); // 마지막 데이터 초기화
}

void newQ(char data[], Data &Player){
	if (i == 6) { // 최대치에 도달했다면
		delQ(Player); // 첫 데이터 삭제
		strcpy(Player.print_data[5], data); // 마지막 자리에 추가
	}
	else strcpy(Player.print_data[i++], data); // 마지막 자리에 추가
}