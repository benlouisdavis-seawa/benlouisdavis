/*
  Ben Davis
  2120919
  04/24/2025
  Lab 2, Task 1, Part 1
  Has functions to initialize the timer,
  start the timer, read the timer, and to
  reset the timer.
*/

#include <stdint.h>
#include "timer.h"

void timer_init(void)
{
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1;
  delay++;
  delay++;
  
  GPTMCTL &= ~0x1;
  GPTMCFG = 0x0000;
  GPTMTAMR = 0x2;
  GPTMTAILR = 16000000;
}

void start_timer(void)
{
  GPTMTAILR = 80000000; // 5 seconds
  GPTMCTL = 0x1;
}

unsigned int read_timer(void)
{
  if ((GPTMRIS & 1) != 0) {
    return 1;
  }
  else {
    return 0;
  }
}

void reset_timer(void)
{
  GPTMICR |= 0x1;
}