/*
  Ben Davis
  2120919
  05/12/2025
  Lab 3, Task 2, Part 1
  Contains definitions for GPIO
  Port E and ADC 0.
  Has initialize and read functions for
  ADC 0 and its GPIO pins.
*/

#ifndef TEMP_H
#define TEMP_H

#include <stdint.h>
#include <stdio.h>

// Takes no input and returns nothing.
// Enables ADC 0 and GPIO Port E.
// Writes to AFSEL and clears DEN
// for Port E 0.
// Sets alt clock for adc 0, enables
// temp reading and sets a 16 cycle
// hold time. Then enables SS3.
void Temp_Init(void);

// Takes no input, returns a float.
// Waits for conversion to be done,
// then retrieves ADC 0 data.
// Converts ADC 0 data to a float
// and then calculates temperature
// (in celsius) based off of data
// sheet equations.
// Then it returns the calculated
// temperature as a float.
float Read_Temp(void);

// GPIO Port E
#define GPIOE_AFSEL (*((volatile uint32_t *)0x4005C420))
#define GPIOE_DEN (*((volatile uint32_t *)0x4005C51C))
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
// ADC 0
#define RCGCADC (*((volatile uint32_t *)0x400FE638))
#define ADCCC (*((volatile uint32_t *)0x40038FC8))
#define ADCACTSS (*((volatile uint32_t *)0x40038000))
#define ADCPSSI (*((volatile uint32_t *)0x40038028))
#define ADCRIS (*((volatile uint32_t *)0x40038004))
#define ADCISC (*((volatile uint32_t *)0x4003800C))
#define ADC0_EMUX (*((volatile uint32_t *)0x40038014))
#define SS3MUX (*((volatile uint32_t *)0x400380A0))
#define SS3EMUX (*((volatile uint32_t *)0x400380B8))
#define SSCTL3 (*((volatile uint32_t *)0x400380A4))
#define SSTSH3 (*((volatile uint32_t *)0x400380BC))
#define SS3DATA (*((volatile uint32_t *)0x400380A8))

#endif // TEMP_H
