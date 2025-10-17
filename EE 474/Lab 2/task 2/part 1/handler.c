/*
  Ben Davis
  2120919
  5/1/2025
  Lab2, part 2, task1
  Function for timer 0 init and 
  timer 0 interrupt handler
*/

#include <stdint.h>
#include "handler.h"
#include "lab2_led.h"

void Timer_init(void)
{
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1;
  delay++;
  delay++;
  
  GPTMCTL &= 0x0;
  GPTMCFG = 0x0000;
  GPTMTAMR = 0x2;
  GPTMTAILR = 16000000;
  GPTMIMR = 0x01;
  
  NVIC_EN0 = 0x80000; // enable interrupt 19v
  GPTMICR = 0x1;
  GPTMCTL = 0x1;
}

void Timer0A_Handler(void)
{
  static int state = 0;
  GPTMICR = 0x01;
  
  switch(state) {
    case 0: GPIODATA_N = 0x02; break;
    case 1: GPIODATA_N |= 0x01; break;
    case 2: GPIODATA_F = 0x10; break;
    case 3: GPIODATA_F |= 0x11; break;
    case 4: GPIODATA_N &= ~0x02; break;
    case 5: GPIODATA_N = 0x0; break;
    case 6: GPIODATA_F &= ~0x10; break;
    case 7: GPIODATA_F = 0x0; break;
    default: break;
  }
  
  state = (state + 1) % 8;
}
