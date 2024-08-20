// ______________________ MAIN PROGRAM (main_task2a.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 2a
* November 2nd, 2023
* This program shows 2 LEDs moving from 4 to 1 in a loop with 1 second delays
*   using interrupts.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

int position; // Tracks the position of thd LEDs

int main(void) {
  task2aSetup();
  task2Timer_init();
  
  while (1) {}
  
  return 0;

}

void Timer0A_Handler() {
  timerA_reset();  // Clears timer flag
  
  // Displays only the bottom LED (LED 4)
  if (position == 0) {
    GPIODATA_N = 0;
    GPIODATA_F = LED4;
    position++;
  }
  
  // Displays the bottom 2 LEDs (LED 4 and LED 3)
  else if (position == 1) {
    GPIODATA_F |= LED3;
    position++;
  }
  
  // Displays only the middle 2 LEDs (LED 3 and LED 2)
  else if (position == 2) {
    GPIODATA_N = LED2;
    GPIODATA_F = LED3;
    position++;
  }
  
  // Displays the top 2 LEDs (LED 2 and LED 1)
  else if (position == 3) {
    GPIODATA_N |= LED1;
    GPIODATA_F = 0;
    position = 4;
  }
  
  // Displays only top LED (LED 1)
  else if (position == 4) {
    GPIODATA_N = LED1;
    position = 0;
  }
  
}