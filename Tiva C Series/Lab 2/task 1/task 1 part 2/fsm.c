/*
  Ben Davis
  2120919
  04/28/2025
  Lab 2, Task 1, Part 2
  Manages the traffic stop-like State Machine that
  controls logic on the TIVA board. Takes the offboard
  buttons as inputs and the offboard LEDs as outputs.
*/

#include <stdint.h>
#include "lab1.h"
#include "led.h"
#include "switch.h"
#include "delay.h"

enum LED_States { off, stop, go, wait } LED_State = off;

void traffic_light_fsm(unsigned int power, unsigned int ped) {
  
  unsigned short delay_result = timer();
  
  switch(LED_State) {
    case off:
      if (power) {
        LED_State = stop; // transition to stop state
      } 
      else {
        LED_State = off;
      }
      break;
    
    case stop:
      delay_reset();
      if (power) {
        LED_State = off;
      }
      else if (ped) {
        LED_State = stop;    // if pedestrian, stay in stop
      }
      else if (delay_result != 0) {
        LED_State = go;
      }
      else {
        LED_State = stop;
      }
      break;
      
    case go:
      delay_reset();
      if (power) {
        LED_State = off;
      }
      else if (ped) {  
        LED_State = wait;           // transition to wait state
        delay_reset();
      }
      else if (delay_result != 0) {
        LED_State = stop;           // transition to stop state
      }
      else {
        LED_State = go;
      }
      break;
    
    case wait:
      delay_reset();
      if (power) {
        LED_State = off;
      }
      else if (delay_result != 0) {
        LED_State = stop;     // immediately go to stop state
      }
      else {
        LED_State = wait;
      }
      break;
      
    default:
      LED_State = off;
      break;
  }
 
  switch(LED_State) {
    case off:
      LED_off(0x2C); // all lights off
      break;
      
    case stop:
      LED_off(0x2C); // all lights off
      LED_on(0x04);   // red LED on
      break;
      
    case go:
      LED_off(0x2C); // all lights off
      LED_on(0x20);  // green LED on
      break;
      
    case wait:
      LED_off(0x20); // green light off
      LED_on(0x08);  // yellow LED on
      break;
      
    default:
      LED_off(0x2C);
      break;
  }
}
