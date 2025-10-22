/*
  Ben Davis
  2120919
  05/04/2025
  Lab 3, Task 1, Part 1

  Contains definitions for NVIC,
  GPIO Ports E, F, and N, 
  ADC 0 and SS3,
  and Timer 0.
*/

#ifndef HEADER
#define HEADER

#include <stdint.h>

// NVIC
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))
// GPIO Ports E,F,N
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400)) // enables port F
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400)) // enables port N
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
// ADC 0 and SS3
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
// Timer 0
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
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