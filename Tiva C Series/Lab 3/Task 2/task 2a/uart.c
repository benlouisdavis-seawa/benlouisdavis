/*
  Ben Davis
  2120919
  05/12/2025
  Lab 3, Task 2, Part 1
  Has functions that allow lines to be sent
  to putty using UART 0.
*/

#include <stdio.h>
#include "uart.h"

void UART_Init(void)
{
  volatile unsigned short delay = 0;
  RCGCUART |= 0x1; // uart 0
  RCGCGPIO |= 0x1; // port a
  delay++;
  delay++;
  delay++;

  GPIOA_AFSEL = 0x3; // set alt func for pa0-1
  GPIOA_PCTL = 0x11; // uart0rx and uart0tx enable
  GPIOA_DEN = 0x03;  //
  GPIOA_Dr4 = 0x1;   // set 4 mA drive for PA

  UART0_CTL = 0x0;      // disable uart
  UART0_IBRD = 0x0008;  // 8 - integer portion baud rate
  UART0_FBRD = 0x002C;  // 44 - fractional portion baud rate
  UART0_LCRH = 0x60;    // 8 bits as msg length
  UART0_CC = 0x5;       // enable clock set in altclk
  ALTCLKCFG = 0x0;      // PIOSC -- 16 MHz
  UART0_CTL = 0x301;    // enable uart
}

void Send_Char(char c)
{
  UART0_DATA = c;

  // wait for process to complete
  while (UART0_FLAG & (1 << 5));
}

void Send_Line(const char *str)
{
  while (*str) {
    Send_Char(*str++);
  }
}
