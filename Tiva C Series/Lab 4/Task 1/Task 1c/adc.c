/*
  Ben Davis
  2120919
  05/20/2025
  Lab 3 Task 1, Part 3

  This has function implementations that initialize
  the internal ADC and reads the boards internal
  temperature.
*/

#include <stdint.h>
#include "tm4c1294ncpdt.h"

void ADC_Init(void) {
  long wait = 0;
  // Set bit 0 in SYSCTL_RCGCADC_R to enable ADC0
    SYSCTL_RCGCADC_R |= 0x01;
  wait++;
  wait++;
  // Power up the PLL
  SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR;
  while (SYSCTL_PLLSTAT_R != 0x1); // wait for PLL to lock
  // Enable PIOSC in the CS bit field in the ADCCC registeR
  ADC0_CC_R = 0x1;
  // ALTCLK field should be programmed to 0x0
  SYSCTL_ALTCLKCFG_R = 0x0;
  // Set ADC sample to 125KS/s
  ADC0_PC_R = 0x01;
  // ADC sample averaging control
  ADC0_SAC_R = 0x3;
  // Disable all sequencers for configuration
  ADC0_ACTSS_R &= ~0x000F;
  // Set ADC0 SS3 to highest priority
  ADC0_SSPRI_R = 0x0123;    
  // Set bits 12-15 to 0x00 to enable software trigger on SS3
  ADC0_EMUX_R &= ~0xF000;
  // Set sample channel for sequencer 3
  ADC0_SSMUX3_R &= 0xFFF0;    
  ADC0_SSMUX3_R += 14;
  // TS0 = 1, IE0 = 1, END0 = 1, D0 = 0
  ADC0_SSCTL3_R = 0x00E;
  // Disable ADC interrupts on SS3 by clearing bit 3
  ADC0_IM_R &= ~0x0008;
  // Re-enable sample sequencer 3
  ADC0_ACTSS_R |= 0x0008;
}

unsigned long ADC_Read(void)
{
  unsigned long result;
  // Set bit 3 to trigger sample start
  ADC0_PSSI_R = 0x008; 
  // Wait for SS3 RIS bit to be set to 1
  while ((ADC0_RIS_R & 0x08) == 0); 
  // Read 12-bit result from ADC from FIFO
  result = ADC0_SSFIFO3_R&0xFFF;
  // Clear SS3 RIS bit to 0 to acknowledge completion
  ADC0_ISC_R = 0x0008;
  return result;
}