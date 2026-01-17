#include"types.h"
#include"adc.h"
#include"adc_defines.h"
u32 adcDVal;
f32 eAR,tdeg;
void Read_LM35(f32 *tdegC,f32 *tdegF)
{

Read_ADC(1,&eAR,&adcDVal);
*tdegC=eAR*100;
*tdegF=((*tdegC*(9/5.0))+32);
}
f32 Read_lm35(u8 Ttype)
{
//f32 tdeg;
Read_ADC(1,&eAR,&adcDVal);
tdeg=eAR*100;
if(Ttype=='c');
else if(Ttype=='f')
tdeg=((tdeg*(9/5.0))+32);
return tdeg;
}
