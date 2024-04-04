/* ʹ�ü�ʱ��ʵ��LED��ˮ��*/

/*
	MODE Ϊ1ʱΪ��ʱ����ˮ��
	MODE Ϊ2ʱΪ��ʱ1s���HelloWorld
	MODE Ϊ3ʱΪ�������������������ʾ
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
	
	//TH0��TL0��16λ��ʱ��ʱ���ɸ�λ�͵�λ
	//������ʱ��λ����256����λ��256ȡģ
	//��C/TΪ0ʱ������ÿ12���𵴼�������һ
	//11.0592MHzΪ����Ƶ��
	//��1/11059200*12Ϊһ������Ҫ�ļ�������С��Ϊ921600
	//921600/16Ϊ57600���ɵõ���ʱ���ĳ�ʼֵΪ7936
	TH0 = 7936 / 256;
	TL0 = 7936 % 256;
	count++;
	
	//ʵ�ּ��1s�ı任�����˼�ʱ����Χ
	//�����ñ���ʹ��ʱ���仯ʮ������ִ��
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