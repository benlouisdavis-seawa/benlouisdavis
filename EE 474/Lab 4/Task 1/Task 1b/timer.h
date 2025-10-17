/*
  Ben Davis
  2120919
  05/12/2025
  Lab 3, Task 2, Part 1
  Has functions that initialize timer 0,
  start timer 0, and to read timer 0's status.
*/

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdio.h>

// No inputs, returns nothing.
// Enables Timer 0 for periodic
// countdown mode.
void Timer_Init(void);

// No inputs, returns nothing.
// Clears the interrupt bit.
// Then sets Timer 0's countdown
// value for 2 seconds.
// Then enables/starts Timer 0.
void Start_Timer(int freq);

// No inputs, returns a short (0 or 1).
// Polls Timer 0's raw interrupt status
// (RIS) bit.
// If it is set, returns a 1.
// If it is clear, returns a 0.
unsigned short Read_Timer(void);

// Timer 0
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define TM0_CTL (*((volatile uint32_t *)0x4003000C))
#define TM0_CFG (*((volatile uint32_t *)0x40030000))
#define TM0_AMR (*((volatile uint32_t *)0x40030004))
#define TM0_AIL (*((volatile uint32_t *)0x40030028))
#define TM0_RIS (*((volatile uint32_t *)0x4003001C))
#define TM0_IC (*((volatile uint32_t *)0x40030024))
#define TM0_ADCEV (*((volatile uint32_t *)0x40038070))

#endif // TIMER_H
