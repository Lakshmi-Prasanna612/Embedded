#include<LPC21xx.h>
#include"delay.h"
#include"types.h"
#include"lcd.h"
#include "rtc.h"
#include"adc.h"
#include"adc_defines.h"
#include"uart.h"
#include"PinConnect.h"
#include"defines.h"
#include"LM35.h"
#include"KeyPdDefines.h"
#include"KeyPd.h"
#define LED 29 //led to indicate the alert mode	p1.29
#define sw 26  //switch is used for interrupt	p1.26
void UART_DisplayNormalTemp(float);
void UART_DisplayOverTemp(float );
void LCDdisplay(void);
void dismenu1(void);
void dismenu2(void);
s32 ReadNumber(u8 );
//LED p1.29
//switch p1.26
//ADC pin p0.28 
//keypad switches are p1.16 to p1.23
/*LCD pins
LCD_DAT 0xff//data lines --P0.3-P0.10
RS 16//P0.8
RW 15 //P0.9
EN 17 //P0.10 */
/*UART pins
p0.0 for transmitting pin
p0.1 for receiving pin*/

 

