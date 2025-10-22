/*
  Connects to putty using UART 0.
  Reads the TIVA internal temperature
  using ADC0, and then sends the 
  temperature to putty using UART 0's TX.
  Uses a 2 second countdown timer to
  space out temperature print messages
  to putty.
*/

#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "temp.h"
#include "timer.h"

char buffer[64];

int main(void)
{
  UART_Init();
  Temp_Init();
  Timer_Init();
  
  while (1)
  {
    /*float test = 22.0;
    snprintf(buffer, sizeof(buffer), "UART test: %.1f\r\n", test);
    Send_Line(buffer);*/
    float temp = Read_Temp();
    snprintf(buffer, sizeof(buffer), "Temperature: %.1f C\r\n", temp);
    Send_Line(buffer);
    
    Start_Timer();
    while (Read_Timer() == 0) {};
  }
}
