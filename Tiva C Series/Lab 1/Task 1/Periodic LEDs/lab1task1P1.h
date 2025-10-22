// TASK_1_PART_1_HEADER
/*
  Ben Davis
  2120919
  04/18/2025
  Enables ports N and F for onboard use
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400)) // enables port F
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400)) // enables port N
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#endif //__HEADER1_H__