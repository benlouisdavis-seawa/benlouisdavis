/*
  I2C communication from the TIVA side.
  Gives output readings to the arduino board.
*/

// include
#include <stdint.h>
#include "tm4c1294ncpdt.h"

// I2C comm functions for the TIVA side
void I2C_Init(void)
{
  volatile short delay = 0;
  SYSCTL_RCGCI2C_R |= 0x80;        // I2C 7
  SYSCTL_RCGCGPIO_R |= 0x08;       // GPIO Port D
  delay++; delay++; delay++;

  // pD 0 and 1
  GPIO_PORTD_AFSEL_R |= 0x03;      // PD 0&1 Alt Function On
  GPIO_PORTD_ODR_R |= 0x02;        // PD1 Open Drain
  GPIO_PORTD_DEN_R |= 0x03;        // digi enable
  GPIO_PORTD_PCTL_R |= 0x00000022;

  I2C7_MCR_R = 0x00000010;
  I2C7_MTPR_R = 0x00000009;
  I2C7_MSA_R = 0x00000076;         // Slave address 0x3B;
}

void I2C_SendData(unsigned char data)
{
  I2C7_MSA_R = 0x00000076;        // slv addr 0x3B and write enable
  I2C7_MDR_R = data;              // enter data
  I2C7_MCS_R = 0x7;               // enable, start and stop bits set
  while(I2C7_MCS_R & 0x1);        // wait until finished
}

