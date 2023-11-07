// _________ Task 1b & 2C Button Setup Program (button.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 1b & Task 2c
* November 2nd, 2023
* This file defines functions for setting up the buttons (switches) as outputs
*   (w/ or w/o interrupts) for port E and for getting which button was pressed.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

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

void extern_switch_interrupts(void) {
  GPIOIM_E  &= ~0x3;    // Mask
  GPIOIS_E  &= ~0x3;    // Edge triggered
  GPIOIBE_E &= ~0x3;    // Single edge
  GPIOIVE_E &= ~0x3;    // Falling edge
  switch_reset();       // Clear any previous interrupt flags
  GPIOIM_E |= 0x3;      // Unmask
  EN0 |= (1 << 4);      // Enables interrupt
  PRI1 |= (1 << 29);    // Sets priority level for Interrupt 4 to be 1
}

unsigned long switch_input(void) {
  return (GPIODATA_E & BUTTONS);  // 0x01 or 0x10 (pressed) or 0 (not pressed)
}

void switch_reset() {
  GPIOICR_E |= 0x3;  // Clear interrupt
}