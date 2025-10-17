/*
  Ben Davis
  2120919
  05/12/2025
  Lab 3, Task 2, Part 1
  Enables and sets Timer 0 for a
  2 second countdown in periodic mode.
*/

#include <stdint.h>
#include <stdio.h>
#include "timer.h"

void Timer_Init(void)
{
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1; // timer 0 enable
  delay++;
  delay++;
  delay++;

  TM0_CTL &= ~0x0101;
  TM0_CFG = 0x0;
  TM0_AMR = 0x2;
}

void Start_Timer(int freq)
{
  TM0_IC |= 0x1;       // interrupt clear
  TM0_AIL = 2 * 1000000 * freq;  // 2 seconds * 1 MHz * freq
  TM0_CTL |= (1 << 5);
  TM0_CTL |= 0x1;
}

unsigned short Read_Timer(void)
{
  if (TM0_RIS & 0x1) {
    return 1;
  }
  else {
    return 0;
  }
}