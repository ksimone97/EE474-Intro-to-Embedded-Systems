// ______________________ Traffic Light Program (.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 4 Task 2a
* November 30th, 2023
* This program creates an FSM that sets the value of each LED depending on what
*   button is pressed at a certain state with a time. Virtual buttons have 2 sec 
*   response time. Virtual LED changes every 5 sec. 
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "lab4.h"
#include "lab4_Inits.h"
#include "SSD2119_Display.h"

enum TL_States {TL_Init, TL_Off, TL_Go, TL_Warn, TL_Stop} TL_State; // initialize states

void TrafficLight(int* countPow, int* countPed) { // counter for on/off and pedestrian
  int button = switch_input();  // calling input
  bool next = false;            // next state boolean
  
  switch(TL_State) {  // Transitions
    case TL_Init:     // Initial state set up
      button = 0;     
      *countPow = 0;
      *countPed = 0;
      TL_State = TL_Off;   // set initial state to off
      break;
    
    case TL_Off:  // Initial state (power off)      
      for (int j = 0; j < 5; j++) {    // goes through for 5 seconds        
        timerA_reset();                // reset timer
        TrafficLightTimer_Init(1);     // set 1 sec timer
        while (!(GPTMRIS & 0x1)) {}    // wait
        button = switch_input(); // check button after a second
        if (button == POWER) {   // Only when button first inputs          
          *countPow += 1;        //increment POWER count
        else {                   // otherwise
          *countPow = 0;         // dount count
        }
        if (*countPow == 2) {  // Check POWER count
          TL_State = TL_Stop;  // Change state to stop
          *countPow = 0;       // reset POWER count
          next = true;         
          break;
        } 
      }
      if (!next) {          // after 5 seconds       
        TL_State = TL_Off;  // stay off
      }
      break;
      
    case TL_Go:  // Go state (green LED lit)
      for (int j = 0; j < 5; j++) {    // goes through for 5 seconds
        timerA_reset();                // reset timer
        TrafficLightTimer_Init(1);     // set 1 sec timer
        while (!(GPTMRIS & 0x1)) {}    // wait
        button = switch_input(); // check button after a second
        if (button == POWER) {   // Only when button SW1 inputs          
          *countPow += 1;        // increment POWER count
          *countPed = 0;         
        }
        else if (button == PED) { // Only when button SW2 inputs 
          *countPow = 0;
          *countPed += 1;         // increment PED count
        }
        else {
          *countPow = 0;    // reset POWER count 
          *countPed = 0;    // reset PED count            
        }
        if (*countPow == 2) {  // Check POWER count
          TL_State = TL_Off;   // Change state to go
          *countPow = 0;       // reset POWER count
          next = true;         
          break;
        } 
        else if (*countPed == 2) {  // Check PED count
          TL_State = TL_Warn;       // Change state to warn
          *countPed = 0;            // reset PED count
          next = true;
          break;
        }
      }
      if (!next) {           // after 5 seconds      
        TL_State = TL_Stop;  // continue to stop state
      }
      break;

    case TL_Warn:  // Warn state (yellow LED lit)
      for (int j = 0; j < 5; j++) { // goes through for 5 seconds
        timerA_reset();             // reset timer
        TrafficLightTimer_Init(1);  // set 1 sec timer
        while (!(GPTMRIS & 0x1)) {} // wait
        button = switch_input();    // check button after a second
        if (button == POWER) {               
          *countPow += 1;           //increment POWER count
        }
        else {
          *countPow = 0;
        }
        if (*countPow == 2) {  // Check POWER count
          TL_State = TL_Off;   // Change state to go
          *countPow = 0;       // reset POWER count
          next = true;
          break;
        } 
      }
      if (!next) {              // after 5 seconds      
        TL_State = TL_Stop;     // continue to stop state
      }
      break;

    case TL_Stop:  // Stop state (red LED lit)
      for (int j = 0; j < 5; j++) { // goes through for 5 seconds
        timerA_reset();             // reset timer
        TrafficLightTimer_Init(1);     // set 1 sec timer
        while (!(GPTMRIS & 0x1)) {}    // wait
        button = switch_input(); // check button after a second
        if (button == POWER) {  // Only when button first inputs          
          *countPow += 1;       //increment POWER count
        }
        else {
          *countPow = 0;
        }
        if (*countPow == 2) {  // Check POWER count
          TL_State = TL_Off;  // Change state to go
          *countPow = 0;       // reset POWER count
          next = true;
          break;
        } 
      }
      if (!next) {         // after 5 seconds      
        TL_State = TL_Go;  // continue to stop state
      }
      break;

    default:  // Default to Stop state
      TL_State = TL_Stop;
      break;
  }

  switch(TL_State) {  // State actions
    
    case TL_Off:  // All LEDs off
      Light_Off(RED);
      Light_Off(YELLOW);
      Light_Off(GREEN);
      break;
  
    case TL_Go:   // Green LED on
      Light_On(GREEN);
      break;

    case TL_Warn: // Yellow LED on
      Light_On(YELLOW);
      break;

    case TL_Stop: // Red LED on
      Light_On(RED);
      break;
  
    default:
      TL_State = TL_Stop;
      break;
  }
  
  for (int j = 0; j < 1000000; j++) {}   // Delay for button inputs  
}