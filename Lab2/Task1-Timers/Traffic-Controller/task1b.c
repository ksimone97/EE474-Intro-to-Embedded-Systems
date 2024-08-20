// ______________________ Task 1b Program (.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 1b
* November 2nd, 2023
* This program creates an FSM that sets the value of each LED depending on what
*   button is pressed at a certain state with a time. Buttons have 2 sec 
*   response time. LED changes every 5 sec.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

enum TL_States {TL_Off, TL_Go, TL_Warn, TL_Stop} TL_State; // initialize states

void task1b(int ticks) { // take in sec
  unsigned long button = switch_input();  // What button was pressed
  int countPow; // initialize POWER BUTTON counter
  int countPed; // initialize PEDESTRIAN BUTTON counter
  
  switch(TL_State) {  // Transitions
    
    case TL_Off:  // Initial state (power off)
      for (int j = 0; j < 1000000; j++) { // delay system input 
        countPow = 0;   // reset count from previous state
      }
      
      if (button == POWER) {              // only when button inputs
        for (int j = 0; j < 2; j++) {     // loop 2 times      
          if (button == POWER) {          // Power button
            task1Timer_init(1);           // set 1 sec timer
            
            while (!(GPTMRIS & 0x1)) {}  // wait
            
            timerA_reset();              // reset timer
            countPow++;                  // increment POWER counter
          }
          else {
            countPow = 0;  // reset POWER counter
          }
        }
      }
      
      if (countPow == 2) {   // check POWER count
        TL_State = TL_Stop;  // Change state to stop
        countPow = 0;        // reset POWER counter
      }
      else {
        TL_State = TL_Off;   // Stay at off
      }
      break;
      
    case TL_Go:  // Go state (green LED lit)
      if ((button == POWER) || (button == PED)) {  // only when button inputs
        timerA_reset();
        
        for (int j = 0; j < 2; j++) {    // loop 2 times  
          if (button == POWER) {         // Power button
            task1Timer_init(1);          // set 1 sec timer
            
            while (!(GPTMRIS & 0x1)) {}  // wait
            
            timerA_reset();              // reset timer
            countPow++;                  // increment POWER counter 
          }
          else {
            countPow =0;                 // reset POWER counter
          }
          
          if (button == PED) {           // Signals a pedestrian
            task1Timer_init(1);          // set 1 sec timer
            
            while (!(GPTMRIS & 0x1)) {}  // wait
            
            timerA_reset();              // reset timer
            countPed++;                  // increment PEDESTRIAN counter 
          }
          else {
            countPed = 0;                // reset PEDESTRIAN counter
          }
        }
        
        if (countPed == 2) {          // Check PEDESTRIAN count
          TL_State = TL_Warn;         // Change state to warn
          countPed = 0;               // reset PEDESTRIAN count
        }
        else if (countPow == 2) {    // Check POWER count
          TL_State = TL_Off;          // Change state to off
          countPow = 0;               // reset POWER count
        }
      }
      else {
        task1Timer_init(5);             // set 5 sec timer
        
        while (!(GPTMRIS & 0x1)) {}     // wait
        
        timerA_reset();                 // reset timer
        TL_State = TL_Stop;             // Change state to stop
      }
      break;

    case TL_Warn:  // Warn state (yellow LED lit)
      for (int j = 0; j < 2; j++) {     // loop 2 times
        if (button == POWER) {          // Check POWER button
          task1Timer_init(1);           // set 1 sec timer
          
          while (!(GPTMRIS & 0x1)) {}   // wait
          
          timerA_reset();               // reset timer
          countPow++;                   // increment POWER count
        }
        else {
          countPow = 0;                 // reset POWER count
        }
      }
      
      if (countPow == 2) {      // Check POWER count
        TL_State = TL_Off;      // Change state to off
        countPow = 0;           // reset POWER count
      }
      else {
        task1Timer_init(5);             // set 5 sec timer
        
        while (!(GPTMRIS & 0x1)) {}     // wait
        
        timerA_reset();                 // reset timer
        TL_State = TL_Stop;             // Continues to stop state
      }
      break;
      
    case TL_Stop:  // Stop state (red LED lit)
      if (button == POWER) {  // Only when button inputs
        for (int j = 0; j < 2; j++) {      // loop 2 times
          if (button == POWER) {           // Check POWER button
            task1Timer_init(1);            // set 1 sec timer
            
            while (!(GPTMRIS & 0x1)) {}    // wait
            
            timerA_reset();                // reset timer
            countPow++;                    //increment POWER count
          }
          else {
            countPow = 0;       // reset POWER count
          }
        }
      }
      
      if (countPow == 2) {  // Check POWER count
        TL_State = TL_Off;  // Change state to go
        countPow = 0;       // reset POWER count
      } 
      else {
        task1Timer_init(5);               // set 5 sec timer
        
        while (!(GPTMRIS & 0x1)) {}      // wait
        
        timerA_reset();                  // reset timer
        TL_State = TL_Go;                // continue to go state
      }
      break;

    default:  // Default to Stop state
      TL_State = TL_Stop;
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
      TL_State = TL_Stop;
      break;
  }
  
  for (int j = 0; j < 1000000; j++) {}   // Delay for button inputs  
}