/*
  Contains definitions of UART 0
  and GPIO Port A.
  Has a function to Initialize UART 0,
  a function to send a char over UART 0,
  and a function to send a line over UART 0.
*/

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdio.h>

// Takes no input, returns nothing.
// Enables UART 0 and GPIO Port A.
// Sets the Port A pins for
// UART Tx and Rx.
// Sets UART 0 with a buad rate
// of 115200, message length of
// 8 bits, and enables the alt clk
// PIOSC - 16 MHz.
// Turns on/enables UART 0.
void UART_Init(void);

// Takes a char as input, returns nothing.
// Inputs char to UART Tx and waits for
// it to finish transmitting.
void Send_Char(char c);

// Takes a char array as input, returns nothing.
// Calls Send_Char and iterates over the array,
// sending one char at a time and incrementing
// the array pointer after each transmission.
void Send_Line(const char *str);

// PIOSC - 16 MHz
#define ALTCLKCFG (*((volatile uint32_t *)0x400FE138))
// UART 0
#define RCGCUART (*((volatile uint32_t *)0x400FE618))
#define UART0_DATA (*((volatile uint32_t *)0x4000C000))
#define UART0_FLAG (*((volatile uint32_t *)0x4000C018))
#define UART0_IBRD (*((volatile uint32_t *)0x4000C024))
#define UART0_FBRD (*((volatile uint32_t *)0x4000C028))
#define UART0_LCRH (*((volatile uint32_t *)0x4000C02C))
#define UART0_CTL (*((volatile uint32_t *)0x4000C030))
#define UART0_CC (*((volatile uint32_t *)0x4000CFC8))
// GPIO Port A
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIOA_AFSEL (*((volatile uint32_t *)0x40058420))
#define GPIOA_Dr4 (*((volatile uint32_t *)0x40058504))
#define GPIOA_DEN (*((volatile uint32_t *)0x4005851C))
#define GPIOA_PCTL (*((volatile uint32_t *)0x4005852C))

#endif // UART_H
