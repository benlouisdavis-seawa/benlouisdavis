// HANDLER_INTERRUPT_HEADER
/*
  Ben Davis
  2120919
  5/1/2025
  Interrupt handler for lab 2, part 2, task 3
*/

#ifndef HANDLER_H
#define HANDLER_H

// states for controlling which LEDs are on
enum LED_state { off, stop, warn, go };

// defines the output values based on the
// current state
void fsm(void);

// clears the interrupt for timer 0 at start
// Transitions states with no conditions.
// STOP -> GO
// GO -> STOP
// WARN -> STOP
// Runs the fsm fucntion to update LEDs.
void Timer0A_Handler(void);

// clears interrupt for timer 1.
// if button is 1, then it:
// !off -> transitions to off, turns off timer 0
// everything else -> transitions to stop, starts timer 0
// if button is 2 then it stops, clears, and restarts timer 0.
// if the state is in go, it transitions to warn.
// if it is not state go, it transitions to stop.
// Regardless of button's value, it stops timer 1, sets button to 0,
// and calls the fsm function to update the LEDs.
void Timer1A_Handler(void);

// initializes timer 0 to count down from 5 seconds.
// clears timer 0's interrupt, and keeps timer 0 off.
// initializes timer 1 to count down from 2 seconds.
// also clears timer 1's interrupt bit and keeps timer 1 off.
void Timer_init(void);

// clears timer 1 interrupt bit and starts timer 1.
// then it checks whether button 1 or 2 was pressed.
// Clears the respective interrupt bit, and sets button (int)
// to 1 if Button 1 was pressed, and 2 if Button 2 was pressed.
void GPIOE_Handler(void);

// Sets up GPIO PE 0 and 1 to take in input for offboard buttons.
// Enables the interrupt function for port E (GPIO), and clears
// both interrupt bits for PE 0 & 1.
void GPIOE_init(void);

// Pins for the timer
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
// timer 0
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
// timer 1
#define GPTMCTL_1 (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_1 (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_1 (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))
#define GPTMIMR_1 (*((volatile uint32_t *)0x40031018))
#define GPTMRIS_1 (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_1 (*((volatile uint32_t *)0x40031024))
#define GPTMIMR_1 (*((volatile uint32_t *)0x40031018))

#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))

#endif // HANDLER_H
