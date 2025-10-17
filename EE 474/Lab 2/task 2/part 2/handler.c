/*
  Ben Davis
  2120919
  5/1/2025
  Lab2, part 2, task2
  Function for init and interrupt handler
*/

#include <stdint.h>
#include "handler.h"
#include "lab2_led.h"

void Timer_init(void)
{
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1;
  delay++;
  delay++;
  
  GPTMCTL &= 0x0;
  GPTMCFG = 0x0000;
  GPTMTAMR = 0x2;
  GPTMTAILR = 16000000;
  GPTMIMR = 0x01;
  
  NVIC_EN0 |= 0x80000; // enable interrupt 19v
  GPTMICR = 0x1;
  GPTMCTL = 0x1;
}

void Timer0A_Handler(void)
{
  GPTMICR = 0x01;
  GPIODATA_N ^= 0x02; // toggle led 1
  
}

void GPIOJ_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x100;
  delay++;
  delay++;
  
  GPIODIR_J &= ~0x03;
  GPIODEN_J = 0x03;
  GPIOPUR_J = 0x03;
  GPIOIM_J = 0x03;
  NVIC_EN1 = (1 << (51 - 32)); // enable interrupt 51v
  GPIOICR_J = 0x1;
}

void GPIOJ_Handler(void)
{
  if (GPIORIS_J & 0x01) {
    GPIOICR_J = 0x01;
    GPTMCTL = 0x0;
    GPIODATA_N = 0x01; // turn off LED1, turn on LED2
  }
  
  if (GPIORIS_J & 0x02) {
    GPIOICR_J = 0x02;
    GPIODATA_N &= ~0x01; // turn off LED2
    GPTMCTL = 0x01;
  }
}
