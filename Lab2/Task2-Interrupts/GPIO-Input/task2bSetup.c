// _________ Task 2b Setup Program (.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 2b
* November 2nd, 2023
* This program sets up ports N and J for the switches and LEDs, such that Port N
*   is an output (LEDs) and Port J is an active low input (SWs) that triggers an
*   interrupt.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

void GPIO_init(void) {  
  
  
  volatile unsigned short delay = 0;
  
  // Enables Port N and Port J
  // N place 12 = 1 0000 0000 0000 = 0x1000
  // J place  8 = 0 0001 0000 0000 = 0x0100
  RCGCGPIO |= 0x1100;
  
  delay++;      // Delay 2 more cycles before access Timer registers
  delay++;      // Refer to Page 756 of Datasheet for info
  
  // Ports N and J settings
  GPIODEN_N = (LED2 | LED1); // Set PN0 and PN1 to digital port
  GPIODEN_J = (SW1 | SW2);   // Set PJ0 and PJ1 to digital port
  GPIODIR_N = (LED2 | LED1); // Set PN0 and PN1 to output
  GPIODIR_J = 0;             // 0 because it is an input
  GPIOPUR_J = (SW1 | SW2);   // Enables Pull Up Resistors (makes SWs active low)
  
  // Interrupt settings
  GPIOIM_J  &= ~0x3;    // Mask
  GPIOIS_J  &= ~0x3;    // Edge triggered
  GPIOIBE_J &= ~0x3;    // Single edge
  GPIOIVE_J &= ~0x3;    // Falling edge
  SW_reset();           // Clears any interrupts
  GPIOIM_J |= 0x3;      // Unmask
  EN1 |= (1 << 19);     // Enables interrupt
  PRI12 &= ~0xE000000;  // Sets priority level for Interrupt 51 to be 0
}

void SW_reset() {
  GPIOICR_J |= 0x3;  // Clear interrupt
}