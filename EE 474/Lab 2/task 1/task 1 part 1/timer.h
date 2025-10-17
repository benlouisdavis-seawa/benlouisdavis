// Lab 2 Timer Header
/*
  Ben Davis
  2120919
  4/24/2025
  Lab 2, Task 1, Part 1
  Header for initializing the timers
*/

#ifndef TIMER_H
#define TIMER_H

// initializes Timer0 to count down for 1 second
// does not start the timer
void timer_init(void);

// changes the count down time to 5 seconds,
// and starts the timer
void start_timer(void);

// returns a 1 if the timer has reached 0,
// and returns 0 if it has not counted down
unsigned int read_timer(void);

// writes to the interrupt clear bit
// to reset the timer for another
// countdown
void reset_timer(void);

// configuration variables for timer 0
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR (*((volatile uint32_t *)0x40030028))
#define GPTMIMR (*((volatile uint32_t *)0x40030018))
#define GPTMRIS (*((volatile uint32_t *)0x4003001C))
#define GPTMICR (*((volatile uint32_t *)0x40030024))

#endif // TIMER_H