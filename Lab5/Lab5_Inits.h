// _________ LAB 5 DRIVERS HEADER FILE (Lab5_Inits.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 5
* December 7th, 2023
* This file has the declarations for the drivers used in lab5.
*/

#ifndef _Lab5_Inits_H_
#define _Lab5_Inits_H_

#define LED4 0x1    // LED 4 (PF0) corresponding to M0PWM0

// Sets up the 16MHz system clock
void TimerA_Init(void);

// Sets up PWM Generator 0 with 1kHz frequency, a 50% duty cycle on pin MnPWM0,
// corresponding to LED4
void PWM_Init(void);

// Brightens the LED
void LED_On(void);

// Dims the LED
void LED_Off(void);

#endif  // _Lab5_Inits_H_
