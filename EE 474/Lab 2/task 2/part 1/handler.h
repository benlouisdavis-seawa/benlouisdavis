// HANDLER_INTERRUPT_HEADER
/*
  Ben Davis
  2120919
  5/1/2025
  Interrupt handler for lab 2, part 2, task 2
*/

#ifndef HANDLER_H
#define HANDLER_H

// writes to the timer 0 interrupt clear.
// then, implements a trivial fsm, changing
// which leds are on and off by lighting up
// and turning off one at a time
void Timer0A_Handler(void);

// sets up timer 0 for a countdown of 1 second
// starts timer 0 when the function is called
void Timer_init(void);

// variable declarations for timer 0
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR (*((volatile uint32_t *)0x40030028))
#define GPTMIMR (*((volatile uint32_t *)0x40030018))
#define GPTMRIS (*((volatile uint32_t *)0x4003001C))
#define GPTMICR (*((volatile uint32_t *)0x40030024))
#define GPTMIMR (*((volatile uint32_t *)0x40030018))
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))

#endif // HANDLER_H
