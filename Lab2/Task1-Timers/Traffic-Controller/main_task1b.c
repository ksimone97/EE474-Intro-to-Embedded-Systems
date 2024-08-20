// ______________________ MAIN PROGRAM (main_task1b.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 1b
* November 2nd, 2023
* This program creates a traffic light controller with two buttons, one acting
*   as power and another signalling a pedestrian being present. When the power
*   is off, no LEDs are on. When the power is on and no buttons are pressed,
*   the LEDs switch from green to red (starting with red). When the pedestrian
*   button is held for 2 seconds, the LEDs go from green to yellow to red (if 
*   held when in Go state) or stays red (if held when in Stop state). The
*   transitions take 5 seconds and only button presses held for 2 seconds are
*   recognized. Presses that aren't held result in delays in each state.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

int main(void) {
  int ticks = 0;  // track seconds passed
  LED_init();  // set up LED
  extern_switch_init();  // set up SWs
  
  while(1) {
    task1b(ticks); // timed traffic light
  }
  return 0;
}
