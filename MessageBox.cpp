#include "stdafx.h"
int i = 6;

void delQ(Data &Player) {
	strcpy(Player.print_data[0], "0");
	for (int j = 1; j < i; j++) {
		strcpy(Player.print_data[j - 1], Player.print_data[j]);
	}
	strcpy(Player.print_data[5], "");
}

void newQ(char data[], Data &Player){
	if (i == 6) {
		delQ(Player);
		strcpy(Player.print_data[5], data);
	}
	else strcpy(Player.print_data[i++], data);
}