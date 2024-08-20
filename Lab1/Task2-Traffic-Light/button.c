// _________ Task 2 Button Setup Program (button.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 2
* October 19th, 2023
* This file defines functions for setting up the buttons (switches) as outputs
*   for port E and for getting which button was pressed.
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task2.h>

void extern_switch_init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10;  // Enable Port E Gating Clock
  delay++;
  delay++;
  
  GPIOAMSEL_E &= ~BUTTONS;  // Disable PE0, PE1 analog function
  GPIOAFSEL_E &= ~BUTTONS;  // Select PE0, PE1 regular function
  GPIODIR_E &= ~BUTTONS;    // Set PE0, PE1 to input direction
  GPIODEN_E |= BUTTONS;     // Enable PE0, PE1 digital function
}

unsigned long switch_input(void) {
  return (GPIODATA_E & BUTTONS);  // 0x01 or 0x10 (pressed) or 0 (not pressed)
}