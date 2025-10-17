// Lab 2 GPIO Header 
/*
  Ben Davis
  2120919
  04/28/2025
  Lab 2, Task 1, Part 2
  Header for intializing Port E for offboard use
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

// GPIO port E variable declarations
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))

#endif //__HEADER1_H__