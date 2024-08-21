// _________ LAB 4 Task 1b main (Lab4_Task1b.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 4 Task 1b
* November 30th, 2023
* This program measures the TM4C's internal temperature at various frequencies 
*   using a PLL and an ADC. It then prints the data to the LCD.
*   Frequencies are manipulated by on-board buttons.
*/

#include "SSD2119_Display.h"
#include "tm4c1294ncpdt.h"
#include "lab4.h"
#include <stdint.h>
#include "Lab3_Inits.h"
#include <stdio.h>

uint32_t ADC_value;

int main(void) {  
  // Select system clock frequency preset
  enum frequency freq = PRESET2;    // 60 MHz
  int freqNum = 60;
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadTemp_Init();    // Initialize ADC0 to read from the temperature sensor
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  SW_Init();             // Initialize SWs as inputs
  LCD_Init();            // initialize LCD
  // floats values to be output
  float temperature;
  float fahrenheit;
  
  while(1) {
    if (GPIODATA_J == SW1) {  // If SW1 pressed, switch frequency to 12MHz
      freq = PRESET3;   // slow freq at 12 MHz
      PLL_Init(freq);   // system clk at 60 MHz
      ADCReadTemp_Init();
      freqNum = 12;
    }  
    else if (GPIODATA_J == SW2) {  // If SW2, switch frequency to 120MHz
      freq = PRESET1;   // speed freq at 120 MHz
      PLL_Init(freq);   // system clk at 60 MHz
      ADCReadTemp_Init();
      freqNum = 120;
    }
    else if (GPIODATA_J != (SW1 | SW2)) {  // If both, frequency back to 60MHz
      freq = PRESET2;   // reset to 60 MHz
      PLL_Init(freq);   // system clk at 60 MHz
      ADCReadTemp_Init();
      freqNum = 60;
    }
    
    // STEP 5: Print the measured temperature in celcius
    // 5.1: Convert ADC_value to in degrees Celcius
    temperature = (147.5 - (247.5 * ADC_value) / 4096); // celcius
    fahrenheit = (temperature * (9.0 / 5.0)) + 32;
    
    //LCD_Printf("The current temperature is %f C, %f F.", temperature, fahrenheit);
    LCD_PrintString("The current temperature is ");
    LCD_PrintFloat(temperature);
    LCD_PrintString(" C, ");
    LCD_PrintFloat(fahrenheit);
    LCD_PrintString(".\n");
    
    // LCD_Printf("The current clock frequency is %d MHz.", freqNum);
    LCD_PrintString("The current clock frequency is ");
    LCD_PrintInteger(freqNum);
    LCD_PrintString(" MHz. ");
    
    // points to coordinates (x,y)
    LCD_SetCursor(0, 0);
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
