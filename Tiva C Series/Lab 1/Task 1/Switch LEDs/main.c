/*
  Ben Davis
  2120919
  04/18/2025
  TASK 1 PART 2
  Uses onboard switches to turn on the onboard
  LEDs PN0-1
*/
#include <stdint.h>
#include "lab1.h"


int main(void)
{
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x1100; // Enable Ports N and J GPIO
   delay++;
   delay++;
   
   GPIODIR_N = 0x03; // setting LEDs as output
   GPIODEN_N = 0x03; // configure to digital port
   
   GPIODIR_J = ~0x03; // set switches as input
   GPIODEN_J = 0x03; // configure digi port
   GPIOPUR_J = 0x03; // set active low
   
   while (1) {
     if (GPIODATA_J == 0x03) {
       GPIODATA_N = 0x00;
     }
     else if (GPIODATA_J == 0x01){
       GPIODATA_N = 0x01;
     }
     else if (GPIODATA_J == 0x02) {
       GPIODATA_N = 0x02;
     }
     else if (GPIODATA_J == 0x00) {
       GPIODATA_N = 0x03;
     }
   }
   
   return 0;
}
