#include"adc_defines.h"
#include<LPC21xx.h>
#include"delay.h"
#include"types.h"
//#include"adc.h"
  void Init_ADC(void)
  {
  //cfg p0.27 -p0.30 as AIN0-AIN3 pins
  PINSEL1&=~(255<<22);
  PINSEL1|=AIN0_PIN_0_27|AIN1_PIN_0_28|AIN2_PIN_0_29|AIN3_PIN_0_30;
  //cfg ADCR a/d control register
  ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
  }
  void Read_ADC(u32  chNo,f32 *eAR,u32 *adcDVal)
  {
  //clear any previous channel selection
  ADCR&=0xffffff00;
  //update req chNo,& start conv
  ADCR|=((1<<ADC_CONV_START_BIT)|(1<<chNo));
  //wait for conv time
  delay_us(3);
  //check if conv completed succesfully
  while(((ADDR>>DONE_BIT)&1)==0);
  //stop adc conversion
  ADCR&=~(1<<ADC_CONV_START_BIT);
  //read digital data
  *adcDVal=((ADDR>>DIGITAL_DATA_BITS)&1023);//adc decimal value
  *eAR=*adcDVal*(3.3/1024);	//equivalent adc value(volts)
  
  }
