/*
  Ben Davis
  2120919
  5/20/25
  Lab 3, Task 1, Part 1

  This function takes an LCD display atached to a TIva board
  and displays a uniform color. In this case, cyan was chosen.
*/

#include <stdint.h>
#include <stdio.h>
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"

int main(void)
{
  LCD_Init();
  LCD_ColorFill(Color4[11]); // cyan
  while (1){};
}