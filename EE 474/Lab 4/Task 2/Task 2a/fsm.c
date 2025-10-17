/*
  Ben Davis
  2120919
  05/27/2025
  Lab 4, Task 2, Part 1

  Implements the Traffic Light System as
  a Finite State Machine. Controls what
  color each of the "lights" (circles)
  on the display screen are. Black if
  off, red/yellow/green if on.
*/

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"

typedef enum {off, stop, wait, go} State;

State state = off;

void fsm(unsigned short pwr, unsigned short walk)
{
  // transitions
  switch(state)
  {
    case off:
      if (pwr & 0x1) { Timer0_Start(); state = stop; }
      else { state = off; }
      break;

    case stop:
      if (pwr & 0x1) { state = off; }
      else if (walk & 0x1) {
        Timer0_Reset();
        state = stop;
      }
      else if (TIMER0_RIS_R & 0x1) {
        TIMER0_ICR_R = 0x1;
        state = go;
      }
      else { state = stop; }
      break;

    case wait:
      if (pwr & 0x1) { state = off; }
      else if (TIMER0_RIS_R) { Timer0_Reset(); state = stop; }
      else { state = wait; }
      break;

    case go:
      if (pwr & 0x1) { Timer0_Reset(); Timer0_Off(); state = off; }
      else if (walk * 0x1) {
        Timer0_Reset();
        state = wait;
      }
      else if (TIMER0_RIS_R & 0x1) {
        TIMER0_ICR_R = 0x1;
        state = stop;
      }
      else { state = go; }
      break;

    default:
      break;
  }

  // output values
  switch(state)
  {
    case off:
      LCD_DrawFilledCircle(60, 50, 30, Color4[0]);   // red light
      LCD_DrawFilledCircle(60, 120, 30, Color4[0]);  // yellow light
      LCD_DrawFilledCircle(60, 190, 30, Color4[0]);  // green light
      break;

    case stop:
      LCD_DrawFilledCircle(60, 50, 30, Color4[12]);  // red light
      LCD_DrawFilledCircle(60, 120, 30, Color4[0]);  // yellow light
      LCD_DrawFilledCircle(60, 190, 30, Color4[0]);  // green light
      break;

    case wait:
      LCD_DrawFilledCircle(60, 50, 30, Color4[0]);   // red light
      LCD_DrawFilledCircle(60, 120, 30, Color4[14]); // yellow light
      LCD_DrawFilledCircle(60, 190, 30, Color4[0]);  // green light
      break;

    case go:
      LCD_DrawFilledCircle(60, 50, 30, Color4[0]);   // red light
      LCD_DrawFilledCircle(60, 120, 30, Color4[0]);  // yellow light
      LCD_DrawFilledCircle(60, 190, 30, Color4[10]); // green light
      break;

    default:
      break;
  }
}

