// _________ Task 1b Program (.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 1b
* October 12th, 2023
* This program sets the value of each LED based upon the corresponding SW being
*   pressed. SW1 turns on LED1, SW2 turns on LED2. The active low is handled in
*   the header file (Lab1Task1.h)
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task1.h>

void task1b(void) {
  
  if (GPIODATA_J == SW1) {                      // GPIODATA_J = 0001 SW1
    GPIODATA_N = LED1;
  
  } else if (GPIODATA_J == SW2) {              // GPIODATA_J = 0010 SW2
    GPIODATA_N = LED2;
  
  } else if (GPIODATA_J != (SW1 | SW2)) {      // GPIODATA_J = 0011 both
    GPIODATA_N = (LED1 | LED2);
    
  } else {                                     // GPIODATA_J = 0000 neither
    GPIODATA_N = 0;
    
  }
}