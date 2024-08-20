// _________ LAB 3 DRIVERS HEADER FILE (Lab3_Inits.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 3
* November 16th, 2023
* This file has the declarations for the drivers used in lab3.
*/

#ifndef _Lab3_Inits_H_
#define _Lab3_Inits_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Defines the LEDs as their values when lit up
#define LED4 0x1   // LED 4 (PF0) corresponding to bit 0
#define LED3 0x10  // LED 3 (PF4) corresponding to bit 4
#define LED2 0x1  // LED 2 (PN0) corresponding to bit 0
#define LED1 0x2  // LED 1 (PN1) corresponding to bit 1

// Defines the Switches as their values when pressed (active low, 0 when set)
#define SW1 0x2  // SW 1 (PJ0) corresponding to bit 01 -> 10
#define SW2 0x1  // SW 2 (PJ1) corresponding to bit 10 -> 01

#define ADCIN 0x08  // 0000 1000
#define SS3 0x08

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes the 4 onboard LEDs.
void LED_Init(void);

// Initializes on board buttons and interrupts
void SW_Init(void);

// Resets button interrupts
void SW_reset(void);

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done.
void ADCReadPot_Init(void);

void ADCReadTemp_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void);

#endif  // _Lab3_Inits_H_
