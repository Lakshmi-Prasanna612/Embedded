/*=============================================================================

File   : adc_LM35_lcd.c
Project name:Time-Stamped Sensor Data Logger

Purpose:A Time-Stamped Sensor Data Logger is a system that continuously or periodically 
records sensor readings along with accurate date and time information into a log file 
for later analysis. It ensures traceability, fault analysis, and historical data tracking,
which are essential in industrial and research applications.

===============================================================================*/
// Header file for LPC21xx register definitions
#include<LPC21xx.h>
#include"mini_headers.h" //headers which are related to this project are included in this file
u32 setpoint=35;         //set point for temp alert
volatile  u8 edit_mode=0;//edit mode flag
static u8 last_min=60;  //for every one minute
f32 t;					//temperature to be stored
s32 hr,mn,sc;			//hour minutes second respectively
int main()
{
//Initialize UART
InitUART();
// Initialize RTC 
RTC_Init();
// Initialize ADC
Init_ADC(1);
// Initialize LCD
InitLCD();
//Initailize keypad
KeyPdInit();

// Set the initial time (hours, minutes, seconds)
        SetRTCTimeInfo(17,23,10);
// Set the initial date (date, month, year)
        SetRTCDateInfo(2,1,2026);
//Set the initial day
        SetRTCDay(5);


IODIR1 |= 1<<LED;//p1.20 is set for output to send the alert msg
while(1)
{
if(edit_mode==0)
{
/* ****To display on UART****   */

t=Read_lm35('c');		    //Reading the temperature value in degree
GetRTCTimeInfo(&hr,&mn,&sc);//Reading the current hour minutes and seconds
if(mn!=last_min)			//Checking for every one minute
{
last_min=mn;
if(t<setpoint)				//Checking wheather the temperature is less than setpoint
{
IOCLR1=1<<LED;				//Clearing the LED pin
UART_DisplayNormalTemp(t);	//This Function is used to display the normal Temperature info
}
else
{
IOSET1=1<<LED;				//Set the LED,if the temp is higher than setpoint
UART_DisplayOverTemp(t);	//This function is used to display the Alert temp info
}
}
/* ****For displaying on LCD****	*/

LCDdisplay();
}
/* ****For editing the RTC info****  */

if(((IOPIN1>>sw)&1)==0)     //switch is pressed
{
delay_ms(10);               //key bouncing
/*to display uart editing mode activated
*** Time Editing Mode Activated *** */
UARTTxStr(" *** Time Editing Mode Activated ***");
UARTTxChar('\n');
edit_mode=1;                //enter edit mode
dismenu1();					//This function is used to display the RTC edit menu
edit_mode=0;                //exit edit mode
CmdLCD(0x01);               //clear the LCD
}
}
}
