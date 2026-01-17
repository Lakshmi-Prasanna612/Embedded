#include<LPC21xx.h>

#include"delay.h"

#include"lcd.h"

#include"types.h"

#include"defines.h"


#define LCD_DAT 0xff//data lines --P0.0-P0.7

#define RS 16//P0.8

#define RW 15 //P0.9

#define EN 17 //P0.10


void InitLCD(void)

{

	//P0.0-P0.10--By default GPIO pins

	IODIR0|=((LCD_DAT<<3)|(1<<RS)|(1<<RW)|(1<<EN));

	         //0x7ff

	//P0.0-P0.10 pis are sel for ouput dir

	delay_ms(20);//min 15 msec required

	CmdLCD(0x30);//8-bit mode enabling

	delay_ms(10);//min. of 5 msec

	CmdLCD(0x30);//8-bit mode enabling

	delay_ms(1);//min. of 160 usec

	CmdLCD(0x30);//8-bit mode enabling

	delay_ms(1);//min. of 160 usec

	CmdLCD(0x38);//8-bit with 5*7 font 1 lines disp

	CmdLCD(0x10);//Display off

	CmdLCD(0x01);//Clear display

	CmdLCD(0x06);//Set cursor move direction

	CmdLCD(0x0f);//Disp ON ,cursor ON with Blinking

}

void CmdLCD(u8 cmd)

{

	IOCLR0=1<<RS;//clear P0.8-->RS of LCD

	DispLCD(cmd);

}

void CharLCD(u8 dat)

{

	IOSET0=1<<RS;//SET P0.8-->RS of LCD

	DispLCD(dat);

}

void DispLCD(u8 val)

{

	IOCLR0=1<<RW;//clear P0.9--->RW of LCD

	WRITEBYTE(IOPIN0,3,val);//write cmd to P0.0-P0.7

	IOSET0=1<<EN;//make (P0.10)En high

	delay_ms(2);//min. of 450 nsec expected

	IOCLR0=1<<EN;//clear P0.10--->EN of LCD

	delay_ms(5);

}

void StrLCD(u8 *ptr)

{

	while(*ptr!='\0')

		CharLCD(*ptr++);

}

void U32LCD(s32 num)

{

	u8 a[10];

	s8 i=0;

	//itoa

	if(num==0)

		CharLCD('0');

	else

	{

		if(num<0)

		{

			num=-num;

			CharLCD('-');

		}

		while(num>0)

		{

			a[i++]=num%10+48;

			num=num/10;

		}

		for(--i;i>=0;i--)

			CharLCD(a[i]);

	}

}

void FltLCD(f32 val)

{ 
u8 ip;

	s8 i=0;

	//ftoa


		if(val<0)

		{
         CharLCD('-');
			val=-val;
  		}
		ip=(int)val;
		   U32LCD(ip);
		            CharLCD('.');
					val=val-ip;
					for(i=0;i<2;i++)
					{
					val=val*10;
					CharLCD((int)val+'0');
					val=val-(int) val;
						 }
}

void StoreCustCharFont(void)

{

	u8 i,LUT[]={0x00,0x00,0x04,0x0c,0x1c,0x1c,0x1c,0x00};;

	for(i=0;i<8;i++)

		CharLCD(LUT[i]);
} 
void tempdegsymbol(void)
{

	u8 i,LUT[]={0x1F,0x11,0x11,0x1F,0x00,0x00,0x00,0x00};;

	for(i=0;i<8;i++)

		CharLCD(LUT[i]);
}






