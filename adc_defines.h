//adc_defines.h
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADCCLK 3000000
#define CLKDIV ((PCLK/ADCCLK)-1)
//define for ADCR sfr
#define CLKDIV_BITS 8
#define PDN_BIT 21
#define ADC_CONV_START_BIT 24
//defines for ADDR sfr
#define DIGITAL_DATA_BITS 6//@6 15 bits
#define DONE_BIT 31
//add more defines as when required

#define AIN0_PIN_0_27 0x00400000
#define AIN1_PIN_0_28 0x01400000
#define AIN2_PIN_0_29 0x05400000
#define AIN3_PIN_0_30 0x15400000
