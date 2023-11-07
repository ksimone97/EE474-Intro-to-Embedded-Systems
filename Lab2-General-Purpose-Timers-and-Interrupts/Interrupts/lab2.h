// _________ HEADER FILE (lab2.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2
* November 2nd, 2023
* This header sets up a periodic timer with interrupts as well as ports F, N, J,
*   and E for the LEDs and switches. It also declares all functions and pin
*   values needed for lab 2.
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

// Enables the clock 
#define RCGCGPIO (*((volatile uint32_t*)0x400FE608))

// Defines the register addresses for timers 0A and 0B
#define RCGCTIMER (*((volatile uint32_t*)0x400FE604))
#define GPTMCTL (*((volatile uint32_t*)0x4003000C))
#define GPTMCFG (*((volatile uint32_t*)0x40030000))
#define GPTMTAMR (*((volatile uint32_t*)0x40030004))
#define GPTMTBMR (*((volatile uint32_t*)0x40030008))
#define GPTMTAILR (*((volatile uint32_t*)0x40030028))
#define GPTMTBILR (*((volatile uint32_t*)0x4003002C))
#define GPTMIMR (*((volatile uint32_t*)0x40030018))
#define GPTMRIS (*((volatile uint32_t*)0x4003001C))
#define GPTMICR (*((volatile uint32_t*)0x40030024))

// Defines the register addresses for configuring interrupts
#define EN0 (*((volatile uint32_t*)0xE000E100))
#define EN1 (*((volatile uint32_t*)0xE000E104))
#define PRI1 (*((volatile uint32_t*)0xE000E404))
#define PRI4 (*((volatile uint32_t*)0xE000E410))
#define PRI5 (*((volatile uint32_t*)0xE000E414))
#define PRI12 (*((volatile uint32_t*)0xE000E430))


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
#define GPIOIS_J (*((volatile uint32_t*)0x40060404))
#define GPIOIBE_J (*((volatile uint32_t*)0x40060408))
#define GPIOIVE_J (*((volatile uint32_t*)0x4006040C))
#define GPIOIM_J (*((volatile uint32_t*)0x40060410))
#define GPIORIS_J (*((volatile uint32_t*)0x40060414))
#define GPIOICR_J (*((volatile uint32_t*)0x4006041C))

// Defines the Switches as their values when pressed (active low, 0 when set)
#define SW1 0x2  // SW 1 (PJ0) corresponding to bit 01 -> 10
#define SW2 0x1  // SW 2 (PJ1) corresponding to bit 10 -> 01


// Defines the register addresses for Port E GPIOs
#define GPIOAMSEL_E (*((volatile uint32_t*)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t*)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t*)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t*)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t*)0x4005C3FC))

#define GPIOIS_E (*((volatile uint32_t*)0x4005C404))
#define GPIOIBE_E (*((volatile uint32_t*)0x4005C408))
#define GPIOIVE_E (*((volatile uint32_t*)0x4005C40C))
#define GPIOIM_E (*((volatile uint32_t*)0x4005C410))
#define GPIORIS_E (*((volatile uint32_t*)0x4005C414))
#define GPIOICR_E (*((volatile uint32_t*)0x4005C41C))

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

// Sets up SWs interrupts
void extern_switch_interrupts();

// Returns the value of whatever SW is pressed
unsigned long switch_input();

// Resets external button interrupts
void switch_reset(); 


// Initializes customizable timer 0A w/o interrupts
void task1Timer_init(int);

// Initializes timer 0A w/o interrupts
void task2Timer_init();

// Initializes timers 0A and 0B with interrupts
void task2cTimer_init();

// Resets timer A
void timerA_reset();

// Resets timer B
void timerB_reset();

// One second delay
void delay();


// Sets up timer and LEDs
void task1aSetup();

// Runs LEDs in a loop
void task1a();


// Contains the FSM that manages the traffic light
void task1b(int);


// Sets LEDs 1-4 as outputs
void task2aSetup();


// Sets up LEDs and SWs
void GPIO_init();

// Resets on board button interrupts
void SW_reset();


// Contains the FSM that manages the traffic light
void task2FSM();

#endif // __HEADER1_H__