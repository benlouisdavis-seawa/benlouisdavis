// LAB_2_LED_HEADER
/*
  Ben Davis
  2120919
  04/30/2025
  Lab 2, Task 2, Part 2
  Enables ports N and F for onboard use of LEDs
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400)) // enables port N
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#endif //__HEADER1_H__
