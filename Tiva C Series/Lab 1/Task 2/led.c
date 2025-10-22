/*
  Ben Davis
  2120919
  04/18/2025
  Initializes Port E for offboard LEDS and
  reads the input from the LEDS
*/

#include <stdint.h>
#include "lab1.h"
#include "led.h"


void LED_init(void)
{
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x10; // Enable Port E
   delay++; // Delay 2 more cycles before access Timer registers
   delay++;
   
   GPIOAMSEL_E &= ~0x2C; // disable analog function of PE 2, 3, & 5
   GPIODIR_E |= 0x2C; // set PE 2, 3, & 5 to output
   GPIOAFSEL_E &= ~0x2C; // set PE 2, 3, & 5 regular port function
   GPIODEN_E |= 0x2C; // enable digital output on PE 2, 3, & 5
   GPIODATA_E &= ~0x2C;
}

void LED_on(unsigned int mask)
{
   GPIODATA_E |= mask; 
}

void LED_off(unsigned int mask)
{
   GPIODATA_E &= ~mask; 
}