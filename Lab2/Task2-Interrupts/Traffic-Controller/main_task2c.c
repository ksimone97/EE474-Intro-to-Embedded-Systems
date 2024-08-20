// ______________________ MAIN PROGRAM (main_task2c.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 2c
* November 2nd, 2023
* This program creates a traffic light controller with two buttons, one acting
*   as power and another signalling a pedestrian being present. When the power
*   is off, no LEDs are on. When the power is on and no buttons are pressed,
*   the LEDs switch from green to red (starting with red). When the pedestrian
*   button is held for 2 seconds, the LEDs go from green to yellow to red (if 
*   held when in Go state) or stays red (if held when in Stop state). The
*   transitions take 5 seconds and only button presses held for 2 seconds are
*   recognized. Presses that aren't held result in delays in each state.
*   Interrupts are used.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

volatile unsigned long previous;

int main(void) {
  LED_init();
  extern_switch_init();
  extern_switch_interrupts();
  task2cTimer_init();
  
  previous = 0;
  
  while (1) {}
  
  return 0;

}

void Timer0A_Handler() {
  timerA_reset();  // Clears interrupt
  task2FSM();  // Goes to next state
}

void Timer0B_Handler() {
  // Disables and resets timer B
  GPTMCTL &= ~0x100;
  timerB_reset();
  
  previous = 0;  // Resets stored button
  
  // Resets and enables timer A
  timerA_reset();
  GPTMCTL |= 0x1;
  
  task2FSM();  // Goes to next state
}

void GPIOE_Handler() {
  unsigned long button = switch_input();  // Stores button press
  int changed = (previous == button) ? 0 : 1;  // Change in button press
  
  // If a change in button press (not held)
  if (changed) {
    if (button == 0) {  // A button was released
      GPTMCTL &= ~0x100;  // Disables timer B
      timerB_reset();  // Clears timer B
      GPTMCTL |= 0x1;  // Enables timer A (resumes switching from red to green)
    }
    else {  // A button is pressed that wasn't before
      GPTMCTL &= ~0x1;  // Disables timer 0A
      timerB_reset();  // Clears timer 0B
      GPTMCTL |= 0x100;  // Enables timer 0B (restarts counting the button hold)
    }
  }
  
  previous = button;  // Updates the stored button
  switch_reset();  // Clears the interrupt
}
