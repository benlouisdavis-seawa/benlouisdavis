/* 
  Ben Davis
  2120919
  04/28/2025
  Lab 2, Task 1, Part 2
  Enables all port options for the offboard buttons
  and has a function for each button to read the input
  from the respective button.
*/

#include <stdint.h>
#include "lab1.h"
#include "switch.h"

void extern_switch_init(void)
{
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x10; // Enable Port E Gating Clock
   delay++;
   delay++;
   GPIOAMSEL_E &= ~0x3; // Disable PE 0-1 analog function
   GPIOAFSEL_E &= ~0x3; // Select PE 0-1 regular port function
   GPIODIR_E &= ~0x3; // Set PE 0-1 to input direction
   GPIODEN_E |= 0x3; // Enable PE 0-1 digital function
}

unsigned long switch0_input(void)
{
   return (GPIODATA_E & 0x1);
}

unsigned long switch1_input(void)
{
   return (GPIODATA_E & 0x2);
}
