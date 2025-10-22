// Lab 2 GPIO Header 
/*
  Ben Davis
  2120919
  5/1/2025
  Lab 2, Task 2, Part 3
  Header for intializing Port E
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

// definitions for GPIO Port E control and interrupts
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))
#define GPIORIS_E (*((volatile uint32_t *)0x4005C414))
#define GPIOICR_E (*((volatile uint32_t *)0x4005C41C))
#define GPIOIM_E (*((volatile uint32_t *)0x4005C410))

#endif //__HEADER1_H__
