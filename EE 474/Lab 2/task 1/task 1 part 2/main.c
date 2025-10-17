/*
  Ben Davis
  2120919
  04/28/2025
  Lab 2, Task 1, Part 2
  Implements a traffic light system, with a power
  switch and a walk button for pedestrians.
*/

#include <stdint.h>
#include "lab1.h"
#include "led.h"
#include "switch.h"
#include "fsm.h"
#include "delay.h"
#include "button.h"


int main(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10;
  delay++;
  delay++;
  
  LED_init();
  extern_switch_init();
  button_init();
  delay_init();
  
  LED_off(0x1C);
  
  while(1) {
    unsigned long power = read_button0();
    unsigned long clear = read_button1();
    traffic_light_fsm(power, clear);      // fsm
  }
     
   return 0;
}