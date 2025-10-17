/*
  Ben Davis
  2120919
  05/27/2025
  Lab 4, Task 2, Part 1

  contains functions that help implement
  the timers and the touch display buttons.
*/

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdio.h>
#include "tm4c1294ncpdt.h"

// Takes no input, gives no output
// Initializes timer 0, timer 1,
// and timer 2.
void Timer_Init(void);

// Gives no input, takes no output
// Starts the 5 second countdown
// that is Timer 0.
void Timer0_Start(void);

// Takes no input, gives no output.
// Turns off Timer 0 through the
// control register.
void Timer0_Off(void);

// Takes no input, gives no output.
// Resets Timer 0. This entails
// disabling the timer, clearing
// interrupts, and resetting the
// coutndown value. Lastly starts
// Timer 0.
void Timer0_Reset(void);

// takes no input, no output.
// Checks if the button is pressed.
// If it is, then it starts the
// 2 second timer.
// if not, it resets the timer.
void Power_Button(void);

// takes no input, no output.
// Checks if the button is pressed.
// If it is, then it starts the
// 2 second timer.
// if not, it resets the timer.
void Walk_Button(void);

// no input, no ouput.
// Clears the interrupt bit,
// and sets local variable
// "pwr" to 1 (button has been
// pressed for 2 seconds).
void Timer1A_Handler(void);

// no input, no ouput.
// Clears the interrupt bit,
// and sets local variable
// "wait" to 1 (button has 
// been pressed for 2 seconds).
void Timer2A_Handler(void);

// no input, returns a short
// returns the local variable
// "pwr".
unsigned short Power(void);

// no input, returns a short.
// this returns the local
// variable "wait".
unsigned short Wait(void);

#endif // TIMER_H