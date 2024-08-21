// _________ LAB 5 DRIVERS (Lab5_Inits.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 5
* December 7th, 2023
* This file has the definitions for the drivers used in lab5.
*/

#include "Lab5_Inits.h"
#include "lab5.h"
#include <stdio.h>
#include <stdint.h>

void TimerA_Init(void) {  
  RCGCTIMER |= 0x1;     
  GPTMCTL &= ~0x1;       // Disables timer
  GPTMCFG = 0x0;         // Selects 32-bit mode
  GPTMTAMR |= 0x2;       // Sets register to be in periodic timer mode
  GPTMTAMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down)
  GPTMTAILR = 16000000;  // 16MHz oscillator
  GPTMCTL |= 0x1;        // Enables timer
}

void PWM_Init(void) {
  RCGCPWM |= 0x1;             // Enable PWM clock
  for (int i = 0; i < 2; i++) {} // Delay
  
  RCGCGPIO |= (1 << 5);       // Enable clock to GPIO port F
  for (int i = 0; i < 2; i++) {} // Delay
  
  GPIODIR_F = LED4;    // Set PF0 to output
  
  GPIOAFSEL_F |= LED4; // Enable alternate pin
  
  GPIOPCTL_F |= 0x6;   // Assign the proper signals to the pin
  
  GPIODEN_F |= LED4;   // Enables PF0 as a digital port
  
  // Configure PWM clock to use the divide and set divider to 2
  PWMCC &= ~(0x1);
  PWMCC |= (1 << 8);
  PWMCC &= ~(0x7); // _000
  
  // Configure PWM generator for countdown mode w/ immediate updates to params
  PWMCTL0 &= ~0x1;
  PWMGENA0 = 0x8C; // 1000 1100 = bits 7, 3, 2
  
  // Load the PWM ticks
  int TicksPerSec = 16000; // 16MHz/1kHz = 16000
  PWMLOAD0 = (TicksPerSec - 1);
  
  PWMCMPA0 = 0;        // Set pulse width of MnPWM0
  
  PWMCTL0 = 0x1;       // Start the timers in PWM generator 0
  
  PWMENABLE |= LED4;   // Enable PWM outputs
}

void LED_On(void) {
  for (int i = 0; i < 16000; i++) {  // Increment
    PWMCMPA0 = i;  // Change the duty cycle
    for (int j = 0; j < 500; j++) {}
  }
}

void LED_Off(void) {
  for (int i = 16000; i > 0; i--) {  // Decrement
    PWMCMPA0 = i;  // Change the duty cycle
    for (int j = 0; j < 500; j++) {}
  }
}