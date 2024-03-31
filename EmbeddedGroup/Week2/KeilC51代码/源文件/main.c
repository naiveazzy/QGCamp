#include <REGX52.H>
#include <intrins.h>
#include <stdio.h>
#include "header.h"

int main() {
	int i;
	while(1) {
		BUZZER = 1;
		P1 = 0x01;
		
		for (i = 0; i < 80; i++) {
			P1 = 0x01;
			P1 <<= i%8;
			
			PrintDigital(i%10);
			
			BUZZER = !BUZZER;
			
			Delay100ms();
		}
	}
	
	return 0;
}

void PrintDigital(int num) {
	switch (num) {
		case 0: P0 = 0x40; break;
		case 1: P0 = 0x79; break;
		case 2: P0 = 0x24; break;
		case 3: P0 = 0x30; break;
		case 4: P0 = 0x19; break;
		case 5: P0 = 0x12; break;
		case 6: P0 = 0x02; break;
		case 7: P0 = 0x78; break;
		case 8: P0 = 0x80; break;
		case 9: P0 = 0x10; break;
		default: break;
	}
}

void Delay100ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

