// _________ Task 2 LED Setup Program (LED.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 2
* October 19th, 2023
* This file defines functions for setting up the LEDs as outputs for port E and
*   for turning on and off LEDs.
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task2.h>

void LED_init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x10;  // Enable Port E Gating Clock
  delay++;
  delay++;
  
  GPIOAMSEL_E &= ~LEDS;  // disable analog function of PE2, PE3, PE5
  GPIODIR_E |= LEDS;     // set PE2, PE3, PE5 to output
  GPIOAFSEL_E &= ~LEDS;  // set PE2, PE3, PE5 regular port function
  GPIODEN_E |= LEDS;     // enable digital output on PE2, PE3, PE5

}

void LED_on(unsigned long led) {
  GPIODATA_E |= led;  // turn on LED connected to provided port
}

void LED_off(unsigned long led) {
  GPIODATA_E &= ~led;  // turn off LED connected to provided port
}