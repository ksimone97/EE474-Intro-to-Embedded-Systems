// _________ LAB 3 Task 1a main (Lab3_Task1a.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 3 Task 1b
* November 16th, 2023
* This program measures the resistance of a potentiometer using an ADC. It then
*   lights up various on-board LEDs corresponding to the resistance range.
*   0-2.49   KOhms : LED1
*   2.5-4.99 KOhms : LED1 and LED2
*   5-7.49   KOhms : LED1, LED2, and LED3
*   7.5-10   KOhms : LED1, LED2, LED3, and LED4
*/

#include <stdint.h>
#include "Lab3_Inits.h"

// STEP 0b: Include your header file here
#include "lab3.h"
#include <stdio.h>

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    resistance = ADC_value / 4095.0 * 10.0;
    
    // Use for testing
    printf("%f\n", resistance);
    
    // 5.2: Change the pattern of LEDs based on the resistance
    if (resistance < 2.5) {
      GPIODATA_N = LED1;
      GPIODATA_F = 0;
    } else if (resistance < 5.0) {
      GPIODATA_N = LED1 | LED2;
      GPIODATA_F = 0;
    } else if (resistance < 7.5) {
      GPIODATA_N = LED1 | LED2;
      GPIODATA_F = LED3;
    } else {
      GPIODATA_N = LED1 | LED2;
      GPIODATA_F = LED3 | LED4;
    }
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC0 |= SS3;
  
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3;
}
