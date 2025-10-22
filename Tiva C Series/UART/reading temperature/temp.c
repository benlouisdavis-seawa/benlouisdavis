/*
  Pulls the TIVA internal temperature
  from ADC 0. Has a function to initialize
  ADC 0 and another function to read
  ADC 0's value.
*/

#include <stdio.h>
#include "temp.h"
#include "uart.h"

void Temp_Init(void)
{
  volatile unsigned short delay = 0;
  RCGCADC = 0x1;
  RCGCGPIO |= 0x10;
  while (delay++ < 10) {};

  GPIOE_AFSEL = 0x1;
  GPIOE_DEN = 0x0;
  ADCACTSS = 0x0;    // disable ss3
  ADCCC = 0x1;       // set to altclkcfg
  ADC0_EMUX = 0x0;   // standard processor
  SS3MUX = 0x0;      // clear
  SS3EMUX = 0x0;     // clear
  SSCTL3 = 0xE;      // enable temp reading and set end bit
  SSTSH3 = 0x4;      // 16 clock hold time
  ADCACTSS = (1<<3); // enable sample sequencer 3
}

float Read_Temp(void)
{
  ADCPSSI = (1 << 3);
  while ((ADCRIS & (1 << 3))) {};

  int voltage = SS3DATA & 0xFFF;
  ADCISC = (1 << 3);
  float temp = 147.5f - (75 * (3.3f * voltage / 4096));
  return temp;
}
