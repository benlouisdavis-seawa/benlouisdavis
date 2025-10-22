/*
  Ben Davis
  2120919
  04/18/2025
  Lab 2, Task 1, Part 1
  Periodically turns the (onboard) LEDs lit
  one by one, keeping all previous on, until
  all are lit, then unlights each one
*/

#include <stdint.h>
#include "header.h"

// STATEON1 has LED1 lit
// STATE_ON2 has LED1 and LED2 lit
// STATE_ON3 has LED1-3 lit
// STATE_ONALL has LED1-4 lit
// STATE_OFF1 has LED 2-4 lit
// STATE_OFF2 has LED 3-4 lit
// STATE_OFF3 has LED 4 lit
// STATE_OFFALL has no LEDs lit
//
// each state goes to the next in value
// until the STATEOFF_ALL, which transitions
// to STATE_ON1
typedef enum {
  STATE_ON1 = 0,
  STATE_ON2,
  STATE_ON3,
  STATE_ONALL,
  STATE_OFF1,
  STATE_OFF2,
  STATE_OFF3,
  STATE_OFFALL
} LED_state;

int main(void)
{
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x1020; // Enable PortF GPIO
   delay++;
   delay++;
   
   GPIODIR_F = 0x11; // Set PF0 and PF4 to output
   GPIODEN_F = 0x11; // Set PF0 and PF4 to digital port
   
   GPIODIR_N = 0x03; // Set PN0 and PN1 to output
   GPIODEN_N = 0x03; // Set PN0 and PN1 to digital port
   
   RCGCTIMER |= 0x1;
   delay++;
   delay++;
  
   GPTMCTL |= 0x1;
   GPTMCFG = 0x0000;
   GPTMTAMR = 0x2;
   GPTMTAILR = 16000000;
   
   LED_state currentState = 0;
   
   while (1) {
     switch(currentState) {
       case STATE_ON1:
         GPIODATA_N = 0x02;
         break;
       case STATE_ON2:
         GPIODATA_N = 0x03;
         break;
       case STATE_ON3:
         GPIODATA_F = 0x10;
         break;
       case STATE_ONALL:
         GPIODATA_F = 0x11;
         break;
       case STATE_OFF1:
         GPIODATA_N = 0x01;
         break;
       case STATE_OFF2:
         GPIODATA_N = 0x00;
         break;
       case STATE_OFF3:
         GPIODATA_F = 0x1;
         break;
       case STATE_OFFALL:
         GPIODATA_F = 0x0;
         break;  
     }
     if (GPTMRIS & 0x01) {
       currentState = (currentState + 1) % 8;
       GPTMICR = 0x01;
     }
   }
   return 0;
}