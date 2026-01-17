#include<LPC21xx.h>
#include"mini_headers.h" //The function which are related to this project are included here
int keypress,edit_flag=0,diskey,dy,i,t1=0,keyenter,k;
s32 HH,MM,SS,D,M,Y,s1;
s32 hour,min,sec,date,month,year,day;
extern  u32 setpoint;
#define BKSP 10
/*   This function is used to display the Normal temp info 
     Normal Operation (Temperature within safe limit):
	 [INFO] Temp: 32.5°C @ 13:45:20 13/05/2025        */
void UART_DisplayNormalTemp(float temp)
{
UARTTxStr("Normal Operation (Temperature within safe limit):");
UARTTxChar('\n');
UARTTxStr("[INFO]Temp:");
UARTTxF32(temp);
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
/*    This Function is used to display the Alert info
      Over-Temperature Alert (Temperature exceeds set point (45°C)):
      [ALERT] Temp: 47.3°C @ 14:10:55 13/05/2025 - OVER TEMP!     */
void UART_DisplayOverTemp(float temp)
{
UARTTxStr("Over-Temperature Alert (Temperature exceeds set point (45°C)):");
UARTTxChar('\n');
UARTTxStr("[ALERT]Temp:");
UARTTxF32(temp);
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
}
/* This function is used to display the info in the format of 
   LCD Display info:
  1st line:  HH:MM:SS  T: XX°C
  2nd line: DD/MM/YY   DAY      */
void LCDdisplay(void)
{
GetRTCTimeInfo(&hour,&min,&sec);    //Getting RTC time info
DisplayRTCTime(hour,min,sec);	    //Displaying RTC time info
				CmdLCD(0x8A);		//line 1 pos 11
				CharLCD('T');		//displaying character t
			    CmdLCD(0x8B);		//line 1 pos 12
				CharLCD(':');		//displaying : symbol
				CmdLCD(0x8C);		//line 1 pos 13
	  U32LCD(Read_lm35('c'));	    //Displaying temp value 
				CmdLCD(0x48);       //Cursor is placed at CGRAM loc
				tempdegsymbol();	//To display 
				CmdLCD(0x8E);       //1 Line pos 14
				CharLCD(1);         //font is read from 8*1+0x40 loc
				delay_s(1);			//delay of one second
				CmdLCD(0x8F);		//line 1 pos 15
				CharLCD('C');		// To display  character C
GetRTCDateInfo(&date,&month,&year);	//Getting RTC date info
DisplayRTCDate(date,month,year);	//Displaying RTC date info
GetRTCDay(&day);					//Getting RTC day
DisplayRTCDay(day);					//Displaying day
}
/* This function is used display the menu 
    LCD Display Info:
    1. EDIT RTC INFO
    2. E.SET POINT	3.EXIT   */
void dismenu1(void)
{
while(1)
{
CmdLCD(0x01);                       //clear the lCD display
CmdLCD(0x80);                       //line 1 pos 1
StrLCD("1.EDIT RC INFO");			//To display 1.EDIT RC INFO
CmdLCD(0xC0);                       //line 2 pos 1
StrLCD("2.EDIT SP");				//To display 2.EDIT SP
CmdLCD(0xCA);						//line 2 pos 11
StrLCD("3.EXIT");					//To display 3.EXIT
while(ColStat());                   //wait for sw press
delay_ms(10);                       //for avoiding keybouncing time.
keypress=KeyVal();					//keypress is used to store the keyval from keypad
switch(keypress)					
{
case 1: dismenu2();	                //RTC edit menu
        break;
case 2:
		CmdLCD(0x01);				//Clearing the LCD
		CmdLCD(0x80);				//line 1 POS 1
		StrLCD("SET TEMP SP:");		//To display SET TEMP sp
		delay_s(1);
		CmdLCD(0x01);				//Clearing the LCD
		StrLCD("enter sp");			//To display ENTER sp
		delay_s(1);
		CmdLCD(0x01);				//Clearing the LCD
		t1=ReadNumber(2);           //Reading value from keypad 
		setpoint=t1;				//to updated the setpoint
		break;
case 3:
		CmdLCD(0x01);
		return ;						//exit 

default :	break;
}
}
}
s32 ReadNumber(u8 digit)
{
s32 val=0;
s32 count =0;
int key;
while(1)
{
while(ColStat());           //wait for sw press
delay_ms(10);               //for avoiding keybouncing time.
key=KeyVal();		
while(!ColStat());          //wait for sw release
delay_ms(20);
if(key==BKSP)
{
if(count>0)
{
count--;
val/=10;
CmdLCD(0x10);
CharLCD(' ');
CmdLCD(0x10);
}
}
else if(key==8)
{
break;
}
else if(key<=9)
{
if(count<digit)
{
val=val*10+key;
U32LCD(key);
count++;
}
}
}
return val;
}

	
/* This function is used to display the menu
1.H 2.M 3.S 4.D        --- 1st Line
5.M 6.Y 7.Day 8.E    --- 2nd Line */
void dismenu2(void)
{
s32 tempHH,tempMM,tempSS,tempDD,tempMON,tempYY,tempDAY;
	GetRTCTimeInfo(&tempHH,&tempMM,&tempSS);    //To get RTC time info
	GetRTCDateInfo(&tempDD,&tempMON,&tempYY);	    //To get RTc date info
	GetRTCDay(&tempDAY);//To get RTC day info

			
while(1)
{						
CmdLCD(0x01);						//Clearing the LCD
CmdLCD(0x80);						//line 1 pos 1
StrLCD("1.H 2.M 3.S 4.D");			//To display the 1st line to edit
CmdLCD(0xC0);						//line 2 pos 1
StrLCD("5.M 6.Y 7.Dy 8.E");			//To display the 2nd to edit
while(ColStat());                   //wait for sw press
			delay_ms(10);           //for avoiding keybouncing time.
			diskey=KeyVal();
	GetRTCTimeInfo(&HH,&MM,&SS);    //To get RTC time info
	GetRTCDateInfo(&D,&M,&Y);	    //To get RTc date info
/*   for editing the hour info	*/
switch(diskey)	  
{
 case 1:
        CmdLCD(0x01);
          t1=ReadNumber(2);
if(t1>0 && t1<25)
tempHH=t1;
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("!Out of Range!");
delay_s(2);
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("enter in range ");
delay_s(2);
 }
 break;


/*  for editing the min info */
case 2:
      CmdLCD(0x01);
		t1=ReadNumber(2);
if(t1>=0 && t1<=59)
tempMM=t1;
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("!Out of Range!");
delay_s(2);
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("enter in range ");
delay_s(2);
}
break;
	
 /*      for editing the sec info  */
case 3:
CmdLCD(0x01);
	t1=ReadNumber(2);
if(t1>=0 && t1<=59)
tempSS=t1;
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("!Out of Range!");
delay_s(2);
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("enter in range ");
delay_s(2);
 }
break;

case 4://for editing the date of the month

CmdLCD(0x01);
		t1=ReadNumber(2);
if(t1>0 && t1<32)
tempDD=t1;
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("!Out of Range!");
delay_s(2);
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("enter in range ");
delay_s(2);
}
break;

case 5:	//for editing the month info

CmdLCD(0x01);
		t1=ReadNumber(2);
if(t1>0 && t1<=12)
tempMON=t1;
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("!Out of Range!");
delay_s(2);
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("enter in range ");
delay_s(2);
}
break;

case 6: // for editing the year inf0
CmdLCD(0x01);
		t1=ReadNumber(4);
if(t1>0 && t1<=4040)
tempYY=t1;
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("!Out Range!");
delay_s(2);
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("enter in range ");
delay_s(2);
 }
break;

case 7://for editing day
 		delay_ms(10);//for avoiding keybouncing time.
		CmdLCD(0x01);
		
		CmdLCD(0x80);
		StrLCD("enter day");
		s1=ReadNumber(1);
if(tempDAY>=0 && tempDAY<=6)
	tempDAY=dy;
else
{
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("!Out of Range!");
delay_s(2);
CmdLCD(0x01);
CmdLCD(0x80);
StrLCD("enter in range ");
delay_s(2);
}		
break;
case 8:

// Set the initial time (hours, minutes, seconds)
        SetRTCTimeInfo(tempHH,tempMM,tempSS);
// Set the initial date (date, month, year)
        SetRTCDateInfo(tempDD,tempMON,tempYY);
//Set the initial day
        SetRTCDay(tempDAY);

   CmdLCD(0x01);//exit
   return ;


   default : break;
}
}
}
		                           
