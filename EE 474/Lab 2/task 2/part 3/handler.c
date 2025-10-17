/*
  Ben Davis
  2120919
  5/1/2025
  Lab2, part 2, task3
  Function for init and interrupt handler
*/

#include <stdint.h>
#include "handler.h"
#include "lab2_gpio.h"

enum LED_state state = off;
volatile int button = 0;

void fsm(void)
{
  switch (state)
  {
    case off:
      GPIODATA_E &= 0x0;
      break;
    case stop:
      GPIODATA_E = 0x4;
      break;
    case warn:
      GPIODATA_E = 0x8;
      break;
    case go:
      GPIODATA_E = 0x20;
      break;
    default:
      GPIODATA_E &= 0x0;
  }
}

void Timer_init(void)
{
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x3;
  delay++;
  delay++;
  
  // timer 0 setup
  GPTMCTL_0 &= 0x0;
  GPTMCFG_0 = 0x0000;
  GPTMTAMR_0 = 0x2;
  GPTMTAILR_0 = 80000000;
  GPTMIMR_0 = 0x01;
  
  // timer 1 setup
  GPTMCTL_1 &= 0x0;
  GPTMCFG_1 = 0x0000;
  GPTMTAMR_1 = 0x2;
  GPTMTAILR_1 = 32000000;
  GPTMIMR_1 = 0x01;
  
  NVIC_EN0 |= 0x280000; // enable interrupt 19v and 21v
  
  // start timers
  GPTMICR_0 = 0x1;
  GPTMICR_1 = 0x1;
  GPTMCTL_0 = 0x0;
}

void Timer0A_Handler(void)
{
  GPTMICR_0 = 0x1;
  
  if (state == stop) {
    state = go;
  }
  else if (state == go) {
    state = stop;
  }
  else if (state == warn) {
    state = stop;
  }
  fsm();
}

void Timer1A_Handler(void)
{
  GPTMICR_1 = 0x1;
  
  switch (button)
  {
    case 1:
      if (state != off) {
        state = off;
        GPTMCTL_0 = 0x0;
      }
      else {
        state = stop;
        GPTMCTL_0 = 0x1;
      }
      break;
      
    case 2:
      GPTMCTL_0 = 0x0;
      GPTMICR_0 = 0x1;
      GPTMTAILR_0 = 80000000;
      GPTMCTL_0 = 0x1;
      if (state == go) {
        state = warn;
      }
      else {
        state = stop;
      }
      break;
    default:
      break;
  }
  
  GPTMCTL_1 = 0x0;
  button = 0;
  fsm();
}

void GPIOE_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10; // Enable Port E
  delay++; // Delay 2 more cycles before access Timer registers
  delay++;

  // button init
  GPIOAMSEL_E &= ~0x3; // Disable PE 0-1 analog function
  GPIOAFSEL_E &= ~0x3; // Select PE 0-1 regular port function
  GPIODIR_E &= ~0x3; // Set PE 0-1 to input direction
  GPIODEN_E |= 0x3; // Enable PE 0-1 digital function
  
  // led init
  GPIOAMSEL_E &= ~0x2C; // disable analog function of PE 2, 3, & 5
  GPIODIR_E |= 0x2C; // set PE 2, 3, & 5 to output
  GPIOAFSEL_E &= ~0x2C; // set PE 2, 3, & 5 regular port function
  GPIODEN_E |= 0x2C; // enable digital output on PE 2, 3, & 5
  GPIODATA_E &= ~0x2C;
  
  GPIOIM_E |= 0x03;
  NVIC_EN0 |= (1 << 4);
  GPIOICR_E |= 0x03;
}

void GPIOE_Handler(void)
{
  GPTMICR_1 = 0x1;
  GPTMCTL_1 = 0x1;
  if (GPIORIS_E & 0x1) {
    GPIOICR_E = 0x01;
    button = 1;
  }
  
  if (GPIORIS_E & 0x02) {
    GPIOICR_E = 0x02;
    button = 2;
  }
}
