/*
  Ben Davis
  2120919
  04/18/2025
  Implements a traffic light system, with a power
  switch and a walk button for pedestrians.
*/

#include <stdint.h>
#include "lab1.h"
#include "led.h"
#include "switch.h"
#include "fsm.h"
#include "timer.h"


int main(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10;
  delay++;
  delay++;
  
  LED_init();
  extern_switch_init();
  timer_init();
  
  LED_off(0x1C);
  
  while(1) {
    unsigned long power = switch0_input();
    unsigned long clear = switch1_input();
    traffic_light_fsm(power, clear);      // fsm
    for (int j = 0; j < 900000; j++) {}   // added delay
  }
     
   return 0;
}