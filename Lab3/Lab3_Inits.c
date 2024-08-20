// _________ LAB 3 DRIVERS (Lab3_Inits.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 3
* November 16th, 2023
* This file has the definitions for the drivers used in lab3.
*/

#include "PLL_Header.h"
#include "Lab3_Inits.h"

// STEP 0a: Include your header file here
#include "lab3.h"

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.

  volatile unsigned short delay = 0;
  
  // Enable Port N and Port F
  // N place 12 = 1 0000 0000 0000 = 0x1000
  // F place  5 = 0 0000 0010 0000 = 0x0020
  RCGCGPIO |= 0x1020;

  delay++;      // Delay 2 more cycles before access Timer registers
  delay++;      // Refer to Page 756 of Datasheet for info
  
  // Enables both Ports
  GPIODEN_N = (LED1 | LED2);  // Set PN1 and PN0 to digital port
  GPIODEN_F = (LED3 | LED4);  // Set PF4 and PF0 to digital port
  
  // Configures Port N as an output
  GPIODIR_N = (LED1 | LED2);  // Set PN1 and PN0 to output
  GPIODIR_F = (LED3 | LED4);  // Set PF4 and PF0 to output
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1;
  
  // 2.2: Delay for RCGCADC (Refer to page 1073)  
  for (int i = 0; i < 3; i++) {}
  
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC0 |= 0x1;

  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  RCGCGPIO |= 0x10;  // Enable Port E Gating Clock
  
  // 2.7: Delay for RCGCGPIO
  for (int i = 0; i < 2; i++) {}
  
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= ADCIN;
  
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~ADCIN;

  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= ADCIN;
  
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS0 &= ~SS3;
  
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX0 |= 0x5000;
  
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSMUX3_0 &= ~0xF;
  
  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3_0 |= 0x6;  // u11u
  ADCSSCTL3_0 &= ~0x9;  // 0110
  
  // 2.15: Set the SS3 interrupt mask
  ADCIM0 |= SS3;
    
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  EN0 |= (1 << 17);
  
  // 2.17: Enable ADC0 SS3
  ADCACTSS0 |= SS3;
}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet
  
  RCGCTIMER |= 0x1;
  GPTMCTL &= ~0x1;       // Disables timer
  GPTMCTL |= (1 << 5);   // Sets timer to trigger ADC
  GPTMCFG = 0x0;         // Selects 32-bit mode
  GPTMTAMR |= 0x2;       // Sets register to be in periodic timer mode
  GPTMTAMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down)
  GPTMTAILR = 16000000;  // 16MHz oscillator
  GPTMADCEV |= 0x1;      // Sets type of trigger to be after timer runs out
  GPTMCTL |= 0x1;        // Enables timer
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
