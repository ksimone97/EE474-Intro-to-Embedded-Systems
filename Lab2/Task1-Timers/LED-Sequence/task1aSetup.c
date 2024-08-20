// _________ Task 1a Setup Program (.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 1a
* November 2nd, 2023
* This program sets up a periodic timer as well as ports N and F for the LEDs
*   as outputs.
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab2Task1.h>

void task1aSetup(void) {
  int seconds = 1;
  
  volatile unsigned short delay = 0;
  
  // Enable Port N and Port F
  // N place 12 = 1 0000 0000 0000 = 0x1000
  // F place  5 = 0 0000 0010 0000 = 0x0020
  RCGCGPIO |= 0x1020;

  delay++;      // Delay 2 more cycles before access Timer registers
  delay++;      // Refer to Page 756 of Datasheet for info
  
  task1Timer_init(seconds);
  
  // Enables both Ports
  GPIODEN_N = (LED1 | LED2);  // Set PN1 and PN0 to digital port
  GPIODEN_F = (LED3 | LED4);  // Set PF4 and PF0 to digital port
  
  // Configures Port N as an output
  GPIODIR_N = (LED1 | LED2);  // Set PN1 and PN0 to output
  GPIODIR_F = (LED3 | LED4);  // Set PF4 and PF0 to output

}