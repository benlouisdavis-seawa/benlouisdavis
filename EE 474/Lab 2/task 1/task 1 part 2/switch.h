// SWITCH_HEADER
/*
  Ben Davis
  2120919
  04/28/2025
  Lab 2, Task 1, Part 2
  Initializes and reads switches
*/
#ifndef SWITCH_H
#define SWITCH_H

// Initializes GPIO from Port E on the board
// and prepares PE0-1 to be inputs
void extern_switch_init(void);

// returns whether button 1 (PE0)
// is pressed or not. 0x0 (not pressed)
// 0x1 (pressed)
unsigned long switch0_input(void);

// returns whether button 2 (PE1)
// is pressed or not. 0x0 (not pressed)
// 0x2 (pressed)
unsigned long switch1_input(void);

#endif // SWITCH_H
