// FSM_HEADER
/*
  Ben Davis
  2120919
  04/18/2025
  Handles a state machine with traffic stop qualities.
  Uses offboard buttons as inputs and offboard LEDs as
  outputs.
*/

#ifndef FSM_H
#define FSM_H

// states for the FSM. Stop, wait, and go correspond with
// the red, yellow, and green LEDs being lit, while all others
// are not lit
typedef enum { off, stop, go, wait } LED_States;

// The current state of the state machine
// LED_States LED_State;

// Takes in two inputs from offboard buttons (power, ped).
// when the power button is pressed, it goes to the off 
// state (when not in the off state originally). If in 
// the off state, it goes to the stop state. Now assuming
// that power is always unpressed, when ped is not pressed
// it alternates between the stop and go state. If ped is pressed
// in the go stop, it transitions to wait, which then goes to
// stop, regardless of ped. If ped is pressed in the stop state
// it stays in the stop state.
void traffic_light_fsm(unsigned int power, unsigned int ped);

#endif // FSM_H