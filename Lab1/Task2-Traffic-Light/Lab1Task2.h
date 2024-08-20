// _________ HEADER FILE (Lab1Task2.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 2
* October 19th, 2023
* This header sets up port E for the LEDs and SWs. It also declares
*   all functions and pin values needed for task 2.
*/

#ifndef __HEADER2_H__
#define __HEADER2_H__

// Enables the clock
#define RCGCGPIO (*((volatile uint32_t*)0x400FE608))

// Defines the register addresses for Port E GPIOs
#define GPIOAMSEL_E (*((volatile uint32_t*)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t*)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t*)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t*)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t*)0x4005C3FC))

// Defines the LEDs as their values when lit up
#define RED 0x04     // 0000 0100
#define YELLOW 0x08  // 0000 1000
#define GREEN 0x20   // 0010 0000
#define LEDS (RED | YELLOW | GREEN)

// Defines the buttons when pressed
#define POWER 0x01  // 0000 0001
#define PED 0x02    // 0000 0010
#define BUTTONS (POWER | PED)

// Sets up RED, YELLOW, and GREEN LEDs as outputs
void LED_init();

// Turns on LED connected to provided port
void LED_on(volatile unsigned long);

// Turn off LED connected to provided port
void LED_off(volatile unsigned long);

// Sets up SWs as inputs
void extern_switch_init();

// Returns the value of whatever SW is pressed
unsigned long switch_input();

// Contains the FSM that manages the traffic light
void task2();

#endif // __HEADER2_H__