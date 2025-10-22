/*
  Ben Davis
  2120919
  05/16/2025
  Lab 3, Task 2, Part 2
  Header file for the init, receive, and send
  functions of uart 2.
*/

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdio.h>

// enables Uart 2 and GPIO Port A.
// Port A pins 6 and 7 connect to the bluetooth
// and its Tx and Rx pins.
// Enables UART 2 with a baud rate of 9600,
// a message length of 8 bits, and uses the
// 16 MHz PIOSC for clocking.
void UART_Init(void);

// Takes a char as input, returns nothing.
// Waits for the TX FIFO to not be full
// before writing in the input char for
// transmission.
void Send_Char(char c);

// Takes no input, returns a char.
// Stalls while the RX FIFO is empty,
// then assigns the received data as
// char c. It then returns c.
char Receive_Char(void);

// PIOSC 16 MHz Clock
#define ALTCLKCFG (*((volatile uint32_t *)0x400FE138))
// UART 2
#define RCGCUART (*((volatile uint32_t *)0x400FE618))
#define UART2_DATA (*((volatile uint32_t *)0x4000E000))
#define UART2_FLAG (*((volatile uint32_t *)0x4000E018))
#define UART2_IBRD (*((volatile uint32_t *)0x4000E024))
#define UART2_FBRD (*((volatile uint32_t *)0x4000E028))
#define UART2_LCRH (*((volatile uint32_t *)0x4000E02C))
#define UART2_CTL (*((volatile uint32_t *)0x4000E030))
#define UART2_CC (*((volatile uint32_t *)0x4000EFC8))
// GPIO Port A
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIOA_AFSEL (*((volatile uint32_t *)0x40058420))
#define GPIOA_Dr4 (*((volatile uint32_t *)0x40058504))
#define GPIOA_DEN (*((volatile uint32_t *)0x4005851C))
#define GPIOA_PCTL (*((volatile uint32_t *)0x4005852C))

#endif // UART_H
