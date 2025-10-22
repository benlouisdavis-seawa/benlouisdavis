/*
  Ben Davis
  2120919
  05/25/2025
  Lab 3, Task 2, Part 1

  Implements the display touch buttons
  on the LCD. First initialize the buttons
  and timers two and three. Also initializes
  timer 0 to input a 5 second delay between 
  the stop and go state cycle. When they are
  pressed they start their respective timer
  and if the timer runs out, its interrupt
  sets a value to return as input.
*/

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "timer.h"

unsigned short pwr = 0;
unsigned short wait = 0;

void Timer_Init(void)
{
  volatile unsigned short delay = 0;
  SYSCTL_RCGCTIMER_R |= 0x3;
  delay++; delay++; delay++;
  
  TIMER0_CTL_R &= ~0x1;
  TIMER0_CFG_R = 0x0000;
  TIMER0_TAMR_R = 0x2;
  TIMER0_TAILR_R = 300000000;

  NVIC_EN0_R |= (1 << 21);
  TIMER1_CTL_R &= ~0x1;
  TIMER1_CFG_R = 0x0000;
  TIMER1_TAMR_R = 0x1;
  TIMER1_TAILR_R = 120000000;
  TIMER1_IMR_R |= 0x1;
  TIMER1_ICR_R = 0x1;

  NVIC_EN0_R |= (1 << 23);
  TIMER2_CTL_R &= ~0x1;
  TIMER2_CFG_R = 0x0000;
  TIMER2_TAMR_R = 0x1;
  TIMER2_TAILR_R = 120000000;
  TIMER2_IMR_R |= 0x1;
  TIMER2_ICR_R = 0x1;
}

void Timer0_Start(void)
{
  TIMER0_CTL_R |= 0x1;
}

void Timer0_Off(void)
{
  TIMER0_CTL_R &= ~0x1;
}

void Timer0_Reset(void)
{
  Timer0_Off();
  TIMER0_TAILR_R = 300000000;
  TIMER0_ICR_R = 0x1;
  Timer0_Start();
}

void Power_Button(void)
{
  unsigned short x = (Touch_ReadX() > 1700) & (Touch_ReadX() < 1950);
  unsigned short y = (Touch_ReadY() > 1350) & (Touch_ReadY() < 1600);
  if (x & y) {
    TIMER1_CTL_R = 0x1;
  }
  else {
    TIMER1_CTL_R = 0x0;
    TIMER1_ICR_R = 0x1;
    TIMER1_TAILR_R = 120000000;
    pwr = 0;
  }
}

void Walk_Button(void)
{
  unsigned short x = (Touch_ReadX() > 1730) & (Touch_ReadX() < 2000);
  unsigned short y = (Touch_ReadY() < 1150) | (Touch_ReadY() > 7100);
  if (x & y) {
    TIMER2_CTL_R = 0x1;
  }
  else {
    TIMER2_CTL_R = 0x0;
    TIMER2_ICR_R = 0x1;
    TIMER2_TAILR_R = 120000000;
    wait = 0;
  }
}

void Timer1A_Handler(void)
{
  TIMER1_ICR_R = 0x1;
  pwr = 1;
}

void Timer2A_Handler(void)
{
  TIMER2_ICR_R = 0x1;
  wait = 1;
}

unsigned short Power(void)
{
  return pwr;
}

unsigned short Wait(void)
{
  return wait;
}