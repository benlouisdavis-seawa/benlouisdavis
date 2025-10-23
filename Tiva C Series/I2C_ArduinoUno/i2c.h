/*
  The I2C files for this project intializes
  TIVA's I2C 7 and Port D as the master in the 
  I2C relationship. Contains the initalize
  function and a function to send data to the 
  arduino board.
*/

#ifndef I2C_H
#define I2C_H

#include "tm4c1294ncpdt.h"

// takes no input or output.
// initializes i2c 7 and port
// d's pins 0 and 1 for the
// SDA and SCL connections.
void I2C_Init(void);

// takes a char input, no output.
// sends one byte to the arduino
// board.
void I2C_SendData(unsigned char);

#endif // I2C_H