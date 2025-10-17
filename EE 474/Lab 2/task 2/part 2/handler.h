// HANDLER_INTERRUPT_HEADER
/*
  Ben Davis
  2120919
  5/1/2025
  Interrupt handler for lab 2, part 2, task 2
*/

#ifndef HANDLER_H
#define HANDLER_H

// writes to the interrupt clear bit for timer0
// xors the led1 bit to toggle it on and off
void Timer0A_Handler(void);

// sets up timer 0 to countdown 1 second,
// enables the timer0a interrupt function,
// and starts timer 0
void Timer_init(void);

// Checks which switch was pressed.
// Writes to the GPIOJ interrupt clear bit.
// If switch 1 is pressed, it turns off timer 0
// and led 1, and turns on led 2.
// If switch 2 is pressed, it turns off led 2
// and starts timer 0.
void GPIOJ_Handler(void);

// sets up gpioj to enable switch 1 and 2
// inputs, enables the gpioj interrupt function
// and clears the interrupt on initialization
void GPIOJ_init(void);

// Pins for the timer
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

// Pins for GPIO Port J
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400)) // enables J port
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIORIS_J (*((volatile uint32_t *)0x40060414))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))
#define NVIC_EN1 (*((volatile uint32_t *)0xE000E104))

#endif // HANDLER_H
