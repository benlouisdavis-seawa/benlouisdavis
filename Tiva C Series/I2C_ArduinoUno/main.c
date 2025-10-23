/*
  Implements the i2c functions
  to toggle two leds connected to the
  arduino board. Initializes the on
  board buttons (PortJ 0 and 1). Each
  pin has its own LED that it controls.
  An LED will not turn on or off until
  its corresponding button has been turned on.
*/

// Includes
#include <stdint.h>
#include <stdio.h>
#include "tm4c1294ncpdt.h"
#include "i2c.h"

int main(void)
{
  I2C_Init();
  // Initialize port j for on board buttons
  SYSCTL_RCGCGPIO_R |= 0x100;  // Port J 0-1
  GPIO_PORTJ_DIR_R &= ~0x03;
  GPIO_PORTJ_DEN_R |= 0x03;
  GPIO_PORTJ_PUR_R |= 0x03;

  while(1)
  {
    unsigned char input = (~GPIO_PORTJ_DATA_R) & 0x3;
    I2C_SendData(input);
  }
}