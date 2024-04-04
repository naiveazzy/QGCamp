/* 使用计时器实现LED流水灯*/

/*
	MODE 为1时为定时器流水灯
	MODE 为2时为定时1s输出HelloWorld
	MODE 为3时为输入数字在数码管上显示
*/

#include <REGX52.H>
#include <intrins.h>
#include <stdio.h>
//#include "header.h"

#define MODE 3

#if MODE == 1

sbit LED = P2^1;

void time0();

void main() 
{
	EA = 1;
	ET0 = 1;
	TMOD = 0x01;
	TH0 = (65536 - (500000 / 12)) / 256;
	TL0 = (65536 - (500000 / 12)) % 256;
	TR0 = 1;
	
	P1 = 0x01;
	LED = 0;
	while(1);
}

void time0() interrupt 1
{
	static char count = 0;
	
	//TH0和TL0在16位计时器时构成高位和低位
	//在运算时高位除以256，低位与256取模
	//当C/T为0时，晶振每12次震荡计数器加一
	//11.0592MHz为晶振频率
	//则1/11059200*12为一秒所需要的计数器大小，为921600
	//921600/16为57600，可得到计时器的初始值为7936
	TH0 = 7936 / 256;
	TL0 = 7936 % 256;
	count++;
	
	//实现间隔1s的变换超出了计时器范围
	//故利用变量使计时器变化十六次再执行
	if (count == 16) {
		if (P1 == 0x80) {
			P1 = 0x01;
		} else {
			P1 <<= 1;
		}
		
		LED = !LED;
		
		count = 0;
	}
}
	
#endif

#if MODE == 2

void Uart_Init(void)	//9600bps@11.0592MHz
{
	PCON &= 0x7F;
	SCON = 0x50;		
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	TL1 = 0xFD;			
	TH1 = 0xFD;			
	ET1 = 0;			
	TR1 = 1;
	EA = 1;
	ES = 1;
}

void UART_SendByte(char Byte)
{
	SBUF = Byte;
	
	while(!TI);
	TI = 0;
}
	
void Delay1000ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main()
{
	int i;
	char str[13] = "Hello World!";
	Uart_Init();
	while(1) {
		
		for (i = 0; i < 13; i++) {
			UART_SendByte(str[i]);
		}
		Delay1000ms();
	}
}



#endif

#if MODE == 3

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

void Uart_Init(void)	//9600bps@11.0592MHz
{
	PCON &= 0x7F;
	SCON = 0x50;		
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	TL1 = 0xFD;			
	TH1 = 0xFD;			
	ET1 = 0;			
	TR1 = 1;
	EA = 1;
	ES = 1;
}

void UART_SendByte(char Byte)
{
	SBUF = Byte;
	
	while(!TI);
	TI = 0;
}

void serial() interrupt 4
{
	char a;
	if (RI)
	{
		a = SBUF;
		RI = 0;
		
		if (a >= '0' && a <= '9')
		{
			PrintDigital(a - '0');
		}
		
	}
	
}

void main()
{
	Uart_Init();
	while(1);
}

#endif