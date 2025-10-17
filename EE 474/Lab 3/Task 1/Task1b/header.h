/*
  Ben Davis
  2120919
  05/07/2025
  Lab 3, Task 1, Part 2

  Contains definitions for NVIC 0,
  GPIO Port J,
  ADC 0 and SS3,
  and Timer 0.
*/

#ifndef HEADER
#define HEADER

#include <stdint.h>

#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400)) // enables J port
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))


#define RCGCADC (*((volatile uint32_t *)0x400FE638))
#define ADCCC (*((volatile uint32_t *)0x40038FC8))
#define ADCACTSS (*((volatile uint32_t *)0x40038000))
#define ADCSSFIFO3 (*((volatile uint32_t *)0x400380A8))
#define ADCEMUX (*((volatile uint32_t *)0x40038014))
#define ADCSSMUX3 (*((volatile uint32_t *)0x400380A0))
#define ADCSSEMUX3 (*((volatile uint32_t *)0x400380B8))
#define ADCSSCTL3 (*((volatile uint32_t *)0x400380A4))
#define ADCIM (*((volatile uint32_t *)0x40038008))
#define ADCISC (*((volatile uint32_t *)0x4003800C))
#define ALTCLKCFG (*((volatile uint32_t *)0x400FE138))

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
#define GPTMCC_0 (*((volatile uint32_t *)0x40030FC8))
#define GPTMADCEV_0 (*((volatile uint32_t *)0x40030070))

#endif // HEADER