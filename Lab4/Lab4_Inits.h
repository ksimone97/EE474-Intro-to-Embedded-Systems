// _________ LAB 4 DRIVERS HEADER FILE (Lab4_Inits.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 4
* November 30th, 2023
* This file has the declarations for the drivers used in lab 4.
*/

#ifndef _Lab4_Inits_H_
#define _Lab4_Inits_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Defines the Switches as their values when pressed (active low, 0 when set)
#define SW1 0x2  // SW 1 (PJ0) corresponding to bit 01 -> 10
#define SW2 0x1  // SW 2 (PJ1) corresponding to bit 10 -> 01

// Defines ADC values passed
#define ADCIN 0x08  // 0000 1000
#define SS3   0x08

// Defines the buttons when pressed
#define POWER 1
#define PED   2

// Define colors for the virtual LED
#define RED    (((0xFF>>3)<<11) | ((0x55>>2)<<5) | (0x55>>3))
#define YELLOW (((0xFF>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3))
#define GREEN  (((0x55>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3))

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes on-screen buttons
void Buttons_Init(void);

// Initialize user inputs
int switch_input(void);

// Initialize virtual lights for traffic light controller
void Lights_Init(void);

// Turn on the given light for traffic light controller
void Light_On(unsigned short color);

// Turn off the given light for traffic light controller
void Light_Off(unsigned short color);

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done. Reads the internal temperature
void ADCReadTemp_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void);

// Initializes custumizable timer for traffic light controller
void TrafficLightTimer_Init(int ticks);

// Reset traffic light timer
void timerA_reset(void);

// FSM for traffic light controller
void TrafficLight(int* countPow, int* countPed);

#endif  // _Lab4_Inits_H_
