/*
  Ben Davis
  2120919
  5/1/2025
  Lab 2, Task 2, Part 2
  Toggles LED 1 at a rate of 1 second. If switch 1
  is pressed, LED 1 turns off and LED 2 is on. If 
  switch 2 is pressed, LED 2 turns off, and LED 1
  goes back to toggling every second
*/

#include <stdint.h>
#include "lab2_led.h"
#include "handler.h"


int main(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1000;
  delay++;
  delay++;
  
  GPIODIR_N = 0x03; // Set PN0 and PN1 to output
  GPIODEN_N = 0x03; // Set PN0 and PN1 to digital port
  
  GPIOJ_init();
  Timer_init();
  
  while(1) {}
     
   return 0;
}
