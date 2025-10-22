/*
  Ben Davis
  2120919
  5/20/25
  Lab 3, Task 1, Part 2

  Displays the internal temperature of the tiva board.
  Can switch between 12 MHz and 120 MHz frequencies
  by using the onboard buttons. Temperature is displayed
  in Celsius and Farenheit.
*/

#include <stdint.h>
#include <stdio.h>
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "pll.h"
#include "button.h"
#include "timer.h"

int main(void)
{
  LCD_Init();
  LCD_ColorFill(Color4[0]); // black
  ADC_Init();
  PLL_Init(12);
  Button_Init();
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
    if (Button1_Read() > 0)
    {
      freq = 12;
    }
    else if (Button2_Read() > 0)
    {
      freq = 120;
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
      "The current temperature is %.2f C, %.2f F.\n"
      "The current clock frequency is %d MHz   \r\n", temp_c, temp_f, freq);
      LCD_Printf(buffer);
      LCD_SetCursor(0,0);
      Start_Timer(freq);
    }
  }
}