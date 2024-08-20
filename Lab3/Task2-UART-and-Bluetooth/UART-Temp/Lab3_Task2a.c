// _________ LAB 3 Task 2a main (Lab3_Task2a.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 3 Task 2a
* November 16th, 2023
* This program builds off of Lab 3 Task 1b. It measures the TM4C's internal
*   temperature using an ADC and transmits the data to a PuTTY terminal.
*/

#include <stdint.h>
#include "Lab3_Inits.h"

// STEP 0b: Include your header file here
#include "lab3.h"
#include <stdio.h>

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2;    // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadTemp_Init();    // Initialize ADC0 to read from the temperature sensor
  UART0_Init();          // Initialize the UART0 for serial communication
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  SW_Init();             // Initialize SWs as inputs

  while(1) {
    if (GPIODATA_J == SW1) {  // If SW1 pressed, switch frequency to 12MHz
      freq = PRESET3;
      PLL_Init(freq);
      ADCReadTemp_Init();
    }  
    else if (GPIODATA_J == SW2) {  // If SW2, switch frequency to 120MHz
      freq = PRESET1;
      PLL_Init(freq);
      ADCReadTemp_Init();
    }
    else if (GPIODATA_J != (SW1 | SW2)) {  // If both, frequency back to 60MHz
      freq = PRESET2;
      PLL_Init(freq);
      ADCReadTemp_Init();
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
  
  // STEP 5: Print the measured temperature in Celsius
  // 5.1: Convert ADC_value to in degrees Celsius
  float temperature = (147.5 - (247.5 * ADC_value) / 4096);
  
  // Stores temp data as a character array for transmission
  char str[30];
  sprintf(str, "Degrees Celsius: %f\r\n\n", temperature);
  
  // Transmits one character at a time
  for(int i = 0; i < 30; i++) {
    while ((UARTFR0 & 0x8) == 0x8) {}  // Wait while busy
    UARTDR0 = str[i];  // Load character
  }
}
