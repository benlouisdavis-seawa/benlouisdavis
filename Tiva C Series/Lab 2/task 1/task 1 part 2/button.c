/*
  Ben Davis
  2120919
  4/24/2025
  Lab 2, Task 1, Part 2
  Contains functions that initializes the timers
  used in tandem with the buttons, and functions
  that read button input
*/

#include <stdint.h>
#include "button.h"
#include "lab1.h"
#include "switch.h"

void button_init(void)
{
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x6;
  delay++;
  delay++;
  
  GPTMCTL_1 &= ~0x1;
  GPTMCFG_1 = 0x0000;
  GPTMTAMR_1 = 0x2;
  GPTMTAILR_1 = 32000000;
  
  GPTMCTL_2 &= ~0x1;
  GPTMCFG_2 = 0x0000;
  GPTMTAMR_2 = 0x2;
  GPTMTAILR_2 = 32000000;
}

unsigned long read_button0(void)
{
  GPTMCTL_1 = 0x01;
  if (switch0_input() == 0) {
    GPTMICR_1 = 0x1;
  }
  
  return (GPTMRIS_1 & 0x01);
}

unsigned long read_button1(void)
{
  GPTMCTL_2 = 0x01;
  if (switch1_input() == 0) {
    GPTMICR_2 = 0x1;
  }
  
  return (GPTMRIS_2 & 0x01);
}
