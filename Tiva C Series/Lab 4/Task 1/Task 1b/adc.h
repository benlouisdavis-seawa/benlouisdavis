/*
  Ben Davis
  2120919
  05/20/2025
  Lab 4 Task 1 Part 2

  ADC Init initializes ADC 0 and SS 3 on the
  board. ADC Read reads the value input to the
  ADC 0 register, and converts it into a temp
  reading in celsius.
*/

#ifndef adc_h
#define adc_h

#include <stdint.h>
#include "tm4c1294ncpdt.h"

// takes no input, outputs nothing
// Initializes ADC 0 and sample
// sequencer 3 for internal board
// temperature reading.
void ADC_Init(void);

// takes no input, returns an unsigned long
// Reads the current value of ADC 0 (internal
// board temperature), and converts it to its
// celsius value
unsigned long ADC_Read(void);

#endif // adc_h
