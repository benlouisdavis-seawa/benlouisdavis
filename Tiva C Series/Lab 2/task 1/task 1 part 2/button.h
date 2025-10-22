// Lab 2 Timer Header
/*
  Ben Davis
  2120919
  4/24/2025
  Lab 2, Task 1, Part 2
  Header for initializing the timers and the
  functions to use the timers
*/

#ifndef TIMER_H
#define TIMER_H

// initializes the buttons' timers for use
// sets timer 1 and 2 for a countdown of 2 seconds
void button_init(void);

// both of these functions do the same things,
// but for different buttons. starts a timer,
// checks if the button is pressed. if it is not pressed
// then the interrupt clear is written to.
// returns the bit of the button pressed
unsigned long read_button0(void);
unsigned long read_button1(void);

// setup registers for timer 1
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_1 (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_1 (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_1 (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))
#define GPTMIMR_1 (*((volatile uint32_t *)0x40031018))
#define GPTMRIS_1 (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_1 (*((volatile uint32_t *)0x40031024))

// variables for setup registers of timer 2
#define GPTMCTL_2 (*((volatile uint32_t *)0x4003200C))
#define GPTMCFG_2 (*((volatile uint32_t *)0x40032000))
#define GPTMTAMR_2 (*((volatile uint32_t *)0x40032004))
#define GPTMTAILR_2 (*((volatile uint32_t *)0x40032028))
#define GPTMIMR_2 (*((volatile uint32_t *)0x40032018))
#define GPTMRIS_2 (*((volatile uint32_t *)0x4003201C))
#define GPTMICR_2 (*((volatile uint32_t *)0x40032024))

#endif // TIMER_H
