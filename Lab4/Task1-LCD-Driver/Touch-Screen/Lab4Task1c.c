// _________ Lab 4 Task 1c main (Lab4_Task1c.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 4 Task 1c
* November 30th, 2023
* This program measures the TM4C's internal temperature at various frequencies 
*   (set by buttons on an LCD) using a PLL and an ADC. It then prints the data 
*   to the LCD. Frequencies are manipulated by virtual buttons on LCD.
*/

#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "lab4.h"
#include <stdint.h>
#include "Lab4_Inits.h"
#include <stdio.h>

uint32_t ADC_value;

int main(void) {  
  LCD_Init();      // Initialize LCD driver
  Buttons_Init();  // Draws the buttons on the LCD
  Touch_Init();    // set up LCD touch
  // Select system clock frequency preset
  enum frequency freq = PRESET2;    // 60 MHz
  int freqNum = 60;
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadTemp_Init();    // Initialize ADC0 to read from the temperature sensor
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  // floats values to be output
  float temperature;
  float fahrenheit;
  
  while(1) {
    /*
    bottom right 2400, 900

    SW1 top left (750, 1250?), bottom right (1500, 900)

    SW2 top left (1750, 1250?) bottom right (2000, 900)

    */

    //printf("x: %d, y: %d\n", Touch_ReadX(), Touch_ReadY());
    if ((Touch_ReadY() >= 950) & (Touch_ReadY() <= 1100)) {  // If within y range
      if ((Touch_ReadX() >= 800) & (Touch_ReadX() <= 1500)) {  // SW1
        freq = PRESET3; // slow freq at 12 MHz
        PLL_Init(freq); // system clk at 60 MHz
        ADCReadTemp_Init(); 
        freqNum = 12;
      }
      else if ((Touch_ReadX() >= 1750) & (Touch_ReadX() <= 2000)) {  // SW2
        freq = PRESET1; // fast freq at 120 MHz
        PLL_Init(freq); // system clk at 60 MHz
        ADCReadTemp_Init();
        freqNum = 120;
      }
    }
        
    // STEP 5: Print the measured temperature in celcius
    // 5.1: Convert ADC_value to in degrees Celcius
    temperature = (147.5 - (247.5 * ADC_value) / 4096); // celcius
    fahrenheit = (temperature * (9.0 / 5.0)) + 32;      
    
    // point to (x,y)
    LCD_SetCursor(0, 0);
    
    //LCD_Printf("The current temperature is %f C, %f F.", temperature, fahrenheit);
    LCD_PrintString("The current temperature is ");
    LCD_PrintFloat(temperature);   // celcius
    LCD_PrintString(" C, ");
    LCD_PrintFloat(fahrenheit);    
    LCD_PrintString(" F. \n");
    
    // LCD_Printf("The current clock frequency is %d MHz.", freqNum);
    LCD_PrintString("The current clock frequency is ");
    LCD_PrintInteger(freqNum);
    LCD_PrintString(" MHz. ");
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
