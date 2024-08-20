// _________ HEADER FILE (Lab1Task1.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 1
* October 12th, 2023
* This header sets up ports F, N and J for the LEDs and SWs. It also declares
*   all functions and pin values needed for task 1a and task 1b.
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

// Enables the clock
#define RCGCGPIO (*((volatile uint32_t*)0x400FE608))

// Defines the register addresses for Port F GPIOs
#define GPIODIR_F (*((volatile uint32_t*)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t*)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t*)0x4005D3FC))

// Defines the LEDs as their values when lit up
#define LED4 0x1   // LED 4 (PF0) corresponding to bit 0
#define LED3 0x10  // LED 3 (PF4) corresponding to bit 4

// Defines the register addresses for Port N GPIOs
#define GPIODIR_N (*((volatile uint32_t*)0x40064400))
#define GPIODEN_N (*((volatile uint32_t*)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t*)0x400643FC))

// Defines the LEDs as their values when lit up
#define LED2 0x1  // LED 2 (PN0) corresponding to bit 0
#define LED1 0x2  // LED 1 (PN1) corresponding to bit 1

// Defines the register addresses for Port J GPIOs
#define GPIODIR_J (*((volatile uint32_t*)0x40060400))
#define GPIODEN_J (*((volatile uint32_t*)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t*)0x400603FC))
#define GPIOPUR_J (*((volatile uint32_t*)0x40060510))

// Defines the Switches as their values when pressed (active low, 0 when set)
#define SW1 0x2  // SW 1 (PJ0) corresponding to bit 01 -> 10
#define SW2 0x1  // SW 2 (PJ1) corresponding to bit 10 -> 01

// Sets LEDs 1-4 as outputs
void task1aSetup();

// Makes LEDs light up 2 at a time, cycling from LED 4 to 1
void task1a();

// Sets the LEDs and SWs as inputs or outputs
void task1bSetup();

// Makes LEDs light up when their corresponding SWs are pressed
void task1b();

// Creates a delay
void delay();

#endif // __HEADER1_H__