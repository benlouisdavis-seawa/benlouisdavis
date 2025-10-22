/*
  Ben Davis
  2120919
  05/20/2025
  Lab 4 Task 1 Part 2

  Contains implementations for on board button use.
  Has functions that intialize the buttons, and reads
  from either button.
*/

#include <stdint.h>
#include "button.h"
#include "tm4c1294ncpdt.h"

void Button_Init(void)
{
  volatile unsigned short delay = 0;
  SYSCTL_RCGCGPIO_R |= 0x100;
  delay++; delay++; delay++;

  GPIO_PORTJ_DIR_R &= ~0x03;
  GPIO_PORTJ_DEN_R |= 0x03;
  GPIO_PORTJ_PUR_R |= 0x03;
}

unsigned short Button1_Read(void)
{
  return (GPIO_PORTJ_DATA_R & 0x1) ? 0 : 1;
}

unsigned short Button2_Read(void)
{
  return (GPIO_PORTJ_DATA_R & 0x2) ? 0 : 1;
}