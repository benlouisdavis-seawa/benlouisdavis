/**
 * EE/CSE 474: Lab3 Task1a main function
 * 
 * Ben Davis
 * 2120919
 * 05/07/2025
 * Lab 3, Task 1, Part 2
 * 
 * I enabled GPIO Port J, and configured the
 * on board buttons for use outside of the superloop.
 * Configured ADC0SS3Handler to update the temperature,
 * and in the superloop it prints the temperature, and
 * changes the clock frequency if a button is pressed.
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include <stdio.h>
#include "Lab3_Inits.h"

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
#include "header.h"

volatile uint32_t ADC_value;
volatile float temperature;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET3; // 12 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  //LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0

  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x100;
  delay++;
  delay++;
  // set up on board buttons for use
  GPIODEN_J = 0x3;
  GPIODIR_J &= ~0x3;
  GPIOPUR_J = 0x3;
  printf("temperature should be here\n"); fflush(stdout);
  while(1) {
    // Print temperature to Terminal I/O
    printf("Temperature: %.2f\n", temperature);
    fflush(stdout);
    // Change the clock period based off of button input
    if (GPIODATA_J & 0x1) {
      PLL_Init(PRESET3);           // 12 MHz
    } else if (GPIODATA_J & 0x2) {
      PLL_Init(PRESET1);           // 120 MHz
    }
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC = 0x8;
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = (ADCSSFIFO3);
  temperature = 147.5 - (75 * (3.3f * ADC_value / 4096.0);
}
