/*
  Ben Davis
  2120919
  4/25/2025
  Lab 2, Task 1, Part 2
  Initializes and handles the timer 0 countdown
  of 5 seconds.
*/

#include <stdint.h>
#include "delay.h"

extern void delay_init(void)
{
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1;
  delay++;
  delay++;
  
  GPTMCTL_0 &= ~0x1;
  GPTMCFG_0 = 0x0000;
  GPTMTAMR_0 = 0x2;
  GPTMTAILR_0 = 80000000;
  GPTMCTL_0 |= 0x1;
}

extern unsigned short timer(void)
{ 
  return (GPTMRIS_0 & 0x01);
}

extern void delay_reset(void)
{
  GPTMICR_0 = 0x1;
}
