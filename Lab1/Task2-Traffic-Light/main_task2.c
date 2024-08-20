// ______________________ MAIN PROGRAM (main_task2.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 2
* October 19th, 2023
* This program creates a traffic light controller with two buttons, one acting
*   as power and another signalling a pedestrian being present. When the power
*   is off, no LEDs are on. When the power is on and no buttons are pressed,
*   the LEDs switch from green to red (starting with green). When the pedestrian
*   button is pressed, the LEDs go from green to yellow to red (if pressed when
*   in Go state) or stays red (if pressed when in Stop state).
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task2.h>


int main(void) {
  LED_init();
  extern_switch_init();
  
  while(1) {
    task2();
  }

  return 0;
}
