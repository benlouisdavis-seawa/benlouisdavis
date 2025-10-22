/*
  Ben Davis
  2120919
  5/2/2025
  Implements a traffic light system, with a power
  switch and a walk button for pedestrians.
  When system is on, it toggles between the green
  and red led, holding each for five seconds. If the
  pedestrian button is pressed for two seconds, it
  lights up the yellow LED if green was the current
  LED. If it was red, it stays on red.
*/

#include <stdint.h>
#include "lab2_gpio.h"
#include "handler.h"


int main(void)
{
  GPIOE_init();
  Timer_init();
  
  while(1) {
    fsm();
  }
     
  return 0;
}
