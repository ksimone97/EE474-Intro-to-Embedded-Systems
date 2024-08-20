// _________ LAB 3 Task 1b main (Lab3_Task1b.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 3 Task 1b
* November 16th, 2023
* This program measures the TM4C's internal temperature at various frequencies 
*   using a PLL and an ADC. It then prints the data to the terminal.
*/

#include <stdint.h>
#include "Lab3_Inits.h"

#include "lab3.h"
#include <stdio.h>

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2;    // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadTemp_Init();    // Initialize ADC0 to read from the temperature sensor
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  SW_Init();             // Initialize SWs as inputs

  float temperature;
  float fahrenheit;
  
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
    
    // STEP 5: Print the measured temperature in celcius
    // 5.1: Convert ADC_value to in degrees Celcius
    temperature = (147.5 - (247.5 * ADC_value) / 4096);
    fahrenheit = (temperature * (9.0 / 5.0)) + 32;
    
    // 5.2: Print the temperature value
    // printf("Frequency: %f\n", freq);
    printf("Celcius: %f\n", temperature);
    printf("Fahrenheit: %f\n\n", fahrenheit);
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
