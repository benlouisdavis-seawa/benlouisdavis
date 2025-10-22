// LAB1_TASK1_HEADER
/*
  Ben Davis
  2120919
  04/18/2025
  Enables ports N and J for Task 1
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400)) // enables N port
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400)) // enables J port
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))

#endif //__HEADER1_H__