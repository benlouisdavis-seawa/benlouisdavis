/*
  Ben Davis
  2120919
  05/20/2025
  Lab 4, Task 1, Part 2

  Button Init intializes the on board buttons
  connected to the GPIO J Port for use.
  Button 1 Read reads input from Button 1.
  Button 2 Read takes input from Button 2.
*/

#ifndef button_h
#define button_h

#include <stdint.h>
#include "tm4c1294ncpdt.h"

// takes no input, outputs nothing.
// configures pins 0 and 1 of GPIO
// Port J for use of the onboard buttons
// as inputs.
void Button_Init(void);

// takes no input, outputs an unsigned short
// returns a 0 if button1 is not pressed,
// and returns a 1 if button1 is pressed.
unsigned short Button1_Read(void);

// takes no input, outputs an unsigned short
// returns a 0 if button2 is not pressed,
// and returns a 1 if button2 is pressed.
unsigned short Button2_Read(void);

#endif // button_h
