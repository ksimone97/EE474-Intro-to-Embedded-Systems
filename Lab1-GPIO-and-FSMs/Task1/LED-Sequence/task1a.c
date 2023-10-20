// _________ Task 1a Program (.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 1a
* October 12th, 2023
* This program sets the value of each LED so that it displays two lights moving
*   from LED 4 to LED 1
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task1.h>

void task1a(void) {
  
  // Displays only the bottom LED (LED 4)
  GPIODATA_N = 0;
  GPIODATA_F = LED4;
  
  delay();
  
  // Displays the bottom 2 LEDs (LED 4 and LED 3)
  GPIODATA_F |= LED3;
  
  delay();
  
  // Displays only the middle 2 LEDs (LED 3 and LED 2)
  GPIODATA_N = LED2;
  GPIODATA_F = LED3;
  
  delay();
  
  // Displays the top 2 LEDs (LED 2 and LED 1)
  GPIODATA_N |= LED1;
  GPIODATA_F = 0;
  
  delay();
  
  // Displays only top LED (LED 1)
  GPIODATA_N = LED1;
  
  delay();

}

void delay(void) {
  for (int j = 0; j < 1000000; j++) {}   // Delay
}