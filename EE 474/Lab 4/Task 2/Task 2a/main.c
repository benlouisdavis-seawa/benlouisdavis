/*
  Ben Davis
  2120919
  5/27/25
  Lab 3, Task 1, Part 2
*/

#include <stdint.h>
#include <stdio.h>
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "timer.h"
#include "tm4c1294ncpdt.h"

unsigned short power;
unsigned short walk;
void fsm(unsigned short pwr, unsigned short walk);

int main(void)
{
  __asm("CPSIE I");
  LCD_Init();
  PLL_Init(60);
  Touch_Init();
  LCD_ColorFill(Color4[7]); // light gray 7
  LCD_DrawFilledCircle(60, 50, 30, Color4[0]);   // red light
  LCD_DrawFilledCircle(60, 120, 30, Color4[0]);  // yellow light
  LCD_DrawFilledCircle(60, 190, 30, Color4[0]);  // green light
  LCD_DrawFilledCircle(240, 60, 40, Color4[0]);  // power button
  LCD_DrawFilledCircle(240, 180, 40, Color4[0]); // wait button
  LCD_SetCursor(228, 58);
  LCD_Printf("Power\r\n");
  LCD_SetCursor(230, 175);
  LCD_Printf("Walk\r\n");
  LCD_SetCursor(50,50);
  Touch_Init();
  Timer_Init();
  unsigned short power;
  unsigned short walk;
  while (1) {
    Power_Button();
    Walk_Button();
    power = Power();
    walk = Wait();
    fsm(power, walk);
  }
}