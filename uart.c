#include<LPC21xx.h>
#include"defines.h"
#include"types.h"
#include"PinConnect.h"
void InitUART(void)
{
//PINSEL0|=0x00000001;
CfgPinFunc(0,0,1);//p0.0 for txd0
 CfgPinFunc(0,1,1);//p0.1 for Rxd0

U0LCR=0x03;	//8 bit wordlength with 1 stop bit
U0LCR|=1<<7;//DLAB=1
U0DLL=97;
U0DLM=0;
U0LCR&=~(1<<7);//DLAB=0
}
s8 UARTRxChar(void)
{
    while(!(READBIT(U0LSR,0)));
    return (U0RBR);
}
void UARTTxChar(s8 ch)
{
U0THR=ch;
while(!(READBIT(U0LSR,6)));

}
void UARTTxStr(s8 *ptr)
{
while(*ptr)
UARTTxChar(*ptr++);
}
void UARTTxU32(s32 num)

{

	u8 a[10];

	s8 i=0;

	//itoa

	if(num==0)

		UARTTxChar('0');

	else

	{

		if(num<0)

		{

			num=-num;

			UARTTxChar('-');

		}

		while(num>0)

		{

			a[i++]=num%10+48;

			num=num/10;

		}

		for(--i;i>=0;i--)

			UARTTxChar(a[i]);

	}

}   
void UARTTxF32(f32 fnum)
{
u32 num,i;
if(num<0)
{
UARTTxChar('-');
fnum=-fnum;
}
num=fnum;
UARTTxU32(num);
UARTTxChar('.');
for(i=0;i<6;i++)
{
fnum=(fnum-num)*10;
num=fnum;
UARTTxChar(num+48);
}
}
/*void UART_DisplayNormalTemp(float temp)
{
 UARTTxStr("[INFO]Temp:");
UARTTxF32(Read_lm35('c'));
UARTTxStr("°C");
UARTTxChar('@');
GetRTCTimeInfo(&hour,&min,&sec);
UARTTxU32(hour);
UARTTxChar(':');
UARTTxU32(min);
UARTTxChar(':');
UARTTxU32(sec);
UARTTxStr(" ");

GetRTCDateInfo(&date,&month,&year);
UARTTxU32(date);
UARTTxChar('/');
UARTTxU32(month);
UARTTxChar('/');
UARTTxU32(year);
UARTTxChar('\n');
}
void UART_DisplayOverTemp(float temp)
{
UARTTxStr("[ALERT]Temp:");
IOSET1=1<<LED;
UARTTxF32(Read_lm35('c'));
UARTTxStr("°C");
UARTTxChar('@');

GetRTCTimeInfo(&hour,&min,&sec);
UARTTxU32(hour);
UARTTxChar(':');
UARTTxU32(min);
UARTTxChar(':');
UARTTxU32(sec);
UARTTxStr(" ");

GetRTCDateInfo(&date,&month,&year);
UARTTxU32(date);
UARTTxChar('/');
UARTTxU32(month);
UARTTxChar('/');
UARTTxU32(year);
UARTTxChar('-');
UARTTxStr("OVER TEMP!");
UARTTxChar('\n');
} */