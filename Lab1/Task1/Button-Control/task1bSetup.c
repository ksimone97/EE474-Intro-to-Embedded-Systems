// _________ Task 1b Setup Program (.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 1b
* October 12th, 2023
* This program sets up ports N and J for the switches and LEDs such that Port N
*   is an output (LEDs) and Port J is an active low input (SWs).
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task1.h>

void task1bSetup(void) {  
  volatile unsigned short delay = 0;
  
  // Enables Port N and Port J
  // N place 12 = 1 0000 0000 0000 = 0x1000
  // J place  8 = 0 0001 0000 0000 = 0x0100
  RCGCGPIO |= 0x1100;
  
  delay++;      // Delay 2 more cycles before access Timer registers
  delay++;      // Refer to Page 756 of Datasheet for info
  
  // Enables both Ports
  GPIODEN_N = (LED2 | LED1);  // Set PN0 and PN1 to digital port
  GPIODEN_J = (SW1 | SW2);    // Set PJ0 and PJ1 to digital port
  
  // Configures Port N as an output
  GPIODIR_N = (LED2 | LED1);  // Set PN0 and PN1 to output
  
  // GPIODIR for Port J will be 0 because it is an input
  GPIODIR_J = 0;
  
  // Enables Pull Up Resistors for Port J (makes SWs active low)
  GPIOPUR_J = (SW1 | SW2);
}