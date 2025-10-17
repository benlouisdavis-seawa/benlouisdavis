/*
  Ben Davis
  2120919
  05/1/2025
  Lab 2, Task 2, Part 1
  Implements an LED sequence where they turn on
  one at a time and then off one at a time
*/

#include <stdint.h>
#include "lab2_led.h"
#include "handler.h"


int main(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1020;
  delay++;
  delay++;
  
  GPIODIR_F = 0x11; // Set PF0 and PF4 to output
  GPIODEN_F = 0x11; // Set PF0 and PF4 to digital port
  
  GPIODIR_N = 0x03; // Set PN0 and PN1 to output
  GPIODEN_N = 0x03; // Set PN0 and PN1 to digital port
  
  Timer_init();
  
  while(1) {}
     
   return 0;
}
