// LED HEADER
/*
  Ben Davis
  2120919
  04/28/2025
  Lab 2, Task 1, Part 2
  LED init and function header
*/

#ifndef LED_H
#define LED_H

// initializes Port E for the LEDs (2, 3, and 5)
void LED_init(void);

// turns on one or multiple LEDs,
// based on the input mask used
// bits 2, 3, & 5
void LED_on(unsigned int mask);

// turns off one or multiple LEDs,
// based off of the input mask
// bits 2, 3, & 5
void LED_off(unsigned int mask);

#endif // LED_H
