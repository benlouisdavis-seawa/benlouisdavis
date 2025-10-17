/*
  Ben Davis
  2120919
  05/16/2025
  Lab 3, Task 2, Part 2
  Enables UART 2, and has functions that can
  send and receive one char.
*/

#include <stdio.h>
#include "uart.h"

void UART_Init(void)
{
  volatile unsigned short delay = 0;
  RCGCUART |= 0x4;           // uart 2
  RCGCGPIO |= 0x1;           // port a
  while (delay++ < 5);

  GPIOA_AFSEL = 0xC0;        // enable PA6-7 for alt func
  GPIOA_PCTL = 0x11000000;   // enable Rx2 and Tx2
  GPIOA_DEN = 0xC0;          // dig enable pa 6-7

  UART2_CTL = 0x0;           // disable uart
  UART2_IBRD = 0x68;         // 104 - integer portion baud rate
  UART2_FBRD = 0xA;          // 10 - fractional portion baud rate
  UART2_LCRH = 0x60;         // 8 bits as msg length
  UART2_CC = 0x5;            // enable clock set in altclk
  ALTCLKCFG = 0x1;           // PIOSC -- 16 MHz
  UART2_CTL = 0x301;         // enable uart, tx, and rx
}

void Send_Char(char c)
{
  while (UART2_FLAG & (1 << 5));  // wait for process to complete
  UART2_DATA = c;                 // sends char over uart
}

char Receive_Char(void)
{
  while (UART2_FLAG & (1 << 4));  // while empty, wait
  char c = UART2_DATA;            // grab received char
  return c;                       //
}
