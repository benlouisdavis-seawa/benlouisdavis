/*
  Implements the functions from uart.h to
  receive inputted characters from Putty,
  and immediately sends the same character
  back to Putty.
*/

#include <stdint.h>
#include <stdio.h>
#include "uart.h"

int main(void)
{
  UART_Init();

  while (1) {
    char c = Receive_Char();
    Send_Char(c);
  }
}