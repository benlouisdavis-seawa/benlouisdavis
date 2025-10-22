// Lab 2 Timer Header
/*
  Ben Davis
  2120919
  4/24/2025
  Lab 2, Task 1, Part 2
  Header for initializing the timers and its functions
*/

#ifndef TIMER_H
#define TIMER_H

// initializes timer 0
// sets timer 0 to count down, and to count
// from 5 seconds. Does start the timer on
// function call.
extern void delay_init(void);

// returns 0 if the timer is not at the
// end of its countdown. returns a 1 if it 
// has counted down for 5 seconds
extern unsigned short timer(void);

// writes to timer 0's interrupt clear bit
// to reset timer 0
extern void delay_reset(void);

// variable declarations for timer 0 setup registers
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

#endif // TIMER_H
