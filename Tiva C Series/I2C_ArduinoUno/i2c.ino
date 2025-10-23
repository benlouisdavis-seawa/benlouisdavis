/*
  i2c.ino

  Ben Davis
  2120919
  06/06/2025
  Lab 5

  Setup()
  Sets up the arduino board for i2c
  connection.
  Enables pins A2 and A3 as outputs.

  Led_switch()
  Reads in the byte of data that the
  Tiva sends through. If the first or
  second bit have been written to, then
  inverts the appropriate LEDn_State
  boolean value. 
  
  loop()
  every cycle, turns on or off the LEDs
  if the corresponding LEDn_State boolean
  was changed.
*/

#include <Wire.h>

bool LED1_State = false;  // output value of LED 1
bool LED2_State = false;  // output value of LED 2

void setup()
{
  Wire.begin(0x3B);
  Wire.onReceive(led_switch);

  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}

void led_switch()
{
  byte data = Wire.read();

  if (data & 0x1) {
    LED1_State = !LED1_State;
  }
  if (data & 0x2) {
    LED2_State = !LED2_State;
  }
}

void loop()
{
  digitalWrite(A2, LED1_State);
  digitalWrite(A3, LED2_State);
}
