// ______________________ Task 2 Program (.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 2
* October 19th, 2023
* This program creates an FSM that sets the value of each LED depending on what
*   button is pressed at a certain state.
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task2.h>

enum TL_States {TL_Off, TL_Go, TL_Warn, TL_Stop} TL_State;

void task2() {
  unsigned long button = switch_input();  // What button was pressed
  
  switch(TL_State) {  // Transitions
    
    case TL_Off:  // Initial state (power off)
      if ((button == POWER) | (button == (POWER | PED)) {  // Turns system on
        TL_State = TL_Go;
      }
      else {  // Stays off
        TL_State = TL_Off;
      }
      break;
      
    case TL_Go:  // Go state (green LED lit)
      if ((button == POWER) | (button == (POWER | PED)) {  // Turns system off
        TL_State = TL_Off;
      }
      else if (button == PED) {  // Signals a pedestrian
        TL_State = TL_Warn;
      }
      else if (button == 0) {  // No pedestrians, continues alternating lights
        TL_State = TL_Stop;
      }
      break;

    case TL_Warn:  // Warn state (yellow LED lit)
      if ((button == POWER) | (button == (POWER | PED)) {  // Turns system off
        TL_State = TL_Off;
      }
      else { // Continues path by going to stop state
        TL_State = TL_Stop;
      }
      break;
      
    case TL_Stop:  // Stop state (red LED lit)
      if ((button == POWER) | (button == (POWER | PED)) {  // Turns system off
        TL_State = TL_Off;
      }
      else if (button == PED) {  // Signals a pedestrian
        TL_State = TL_Stop;
      }
      else if (button == 0) {  // No pedestrians, continues alternating lights
        TL_State = TL_Go;
      }
      break;

    default:  // Default to Go state
      TL_State = TL_Go;
      break;
  }

  switch(TL_State) {  // State actions
    
    case TL_Off:  // All LEDs off
      LED_off(RED | YELLOW | GREEN);
      break;
  
    case TL_Go:  // Green LED on
      LED_off(RED | YELLOW);
      LED_on(GREEN);
      break;

    case TL_Warn:  // Yellow LED on
      LED_off(RED | GREEN);
      LED_on(YELLOW);
      break;

    case TL_Stop:  // Red LED on
      LED_off(GREEN | YELLOW);
      LED_on(RED);
      break;
  
    default:
      break;
  }
  
  for (int j = 0; j < 1000000; j++) {}   // Delay       
}