/*
  Ben Davis
  2120919
  5/20/25
  Lab 4, Task 1, Part 3
  
  Displays the boards internal temperature
  on the LCD in Farenheit and Celsius. Has
  two touch buttons that can switch between
  a 12 MHz and 120 MHz system frequency.
*/

#include <stdint.h>
#include <stdio.h>
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "pll.h"
#include "timer.h"

int main(void)
{
  LCD_Init();
  LCD_ColorFill(Color4[0]); // black
  LCD_DrawFilledCircle(80, 180, 50, Color4[3]);
  LCD_DrawFilledCircle(240, 180, 50, Color4[3]);
  LCD_SetCursor(60, 180);
  LCD_Printf("12 MHz\r\n");
  LCD_SetCursor(220, 180);
  LCD_Printf("120 MHz");
  LCD_SetCursor(0,0);
  ADC_Init();
  PLL_Init(12);
  Touch_Init();
  char buffer[128];
  int freq = 12;
  int prev_freq = 12;
  unsigned long voltage;
  float temp_c;
  float temp_f;
  Timer_Init();
  Start_Timer(12);
  while (1)
  {
    if ((Touch_ReadX() < 700) | (Touch_ReadY() < 500))
    {
      // pass, do nothing
    }
    else if ((Touch_ReadX() > 830) & (Touch_ReadX() < 1430))
    {
      if ((Touch_ReadY() > 650) & (Touch_ReadY() < 1200))
      {
        freq = 12;
      }
    }
    else if ((Touch_ReadX() > 1680) & (Touch_ReadX() < 2000))
    {
      if ((Touch_ReadY() > 650) & (Touch_ReadY() < 1200))
      {
        freq = 120;
      }
    }
    else
    {
      // pass
    }

    if (freq != prev_freq)
    {
      PLL_Init(freq);
      Start_Timer(freq);
      prev_freq = freq;
    }

    if (Read_Timer() != 0)
    {
      voltage = ADC_Read();
      temp_c = 147.5f - (75 * (3.3f * voltage / 4096));
      temp_f = (temp_c * 9.0 / 5.0) + 32.0;
      snprintf(buffer, sizeof(buffer), 
      "The current temperature is %.2f C, %.2f F.\n", temp_c, temp_f, freq);
      LCD_Printf(buffer);
      LCD_SetCursor(0,0);
      Start_Timer(freq);
    }
  }
}