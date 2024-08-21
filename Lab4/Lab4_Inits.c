// _________ LAB 4 DRIVERS (Lab4_Inits.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 4
* November 30th, 2023
* This file has the definitions for the drivers used in lab4.
*/

#include "PLL_Header.h"
#include "Lab4_Inits.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "lab4.h"
#include <stdio.h>

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

void Buttons_Init(void) {  // Virtual buttons set up
  // dimensions of the LCD in pixels
  // #define LCD_HEIGHT 240
  // #define LCD_WIDTH 320
  unsigned short x1 = 20;               // X-coordinate SW1
  unsigned short y = 100;               // Y-coordinate SWs
  short width = 115;                    // Width SWs
  short height = 75;                    // Height SWs
  unsigned short x2 = x1 + width + 50;  // X-coordinate SW2
  unsigned short color = Color4[5];     // initialize color to magenta
  // Draw the SWs
  LCD_DrawFilledRect(x1, y, width, height, color); 
  LCD_DrawFilledRect(x2, y, width, height, color);
  // Point to the SWs
  LCD_SetCursor(70, 140);
  LCD_PrintString("SW1");
  LCD_SetCursor(70 + width + 50, 140);
  LCD_PrintString("SW2");
}

void SW_Init(void) {  // set up on-board SWs for altering frequency (1b)
  // TASK1B STEP 1: Initialize the 2 on board SWs by initializing the
  // corresponding GPIO pins
  volatile unsigned short delay = 0;
  // Enables Port J
  // J place  8 = 0 0001 0000 0000 = 0x0100
  RCGCGPIO |= 0x0100;
  // Delay 2 more cycles before access Timer registers
  for (int i = 0; i < 2; i++) {}
  // Port J settings
  GPIODEN_J = (SW1 | SW2);   // Set PJ0 and PJ1 to digital port
  GPIODIR_J = 0;             // 0 because it is an input
  GPIOPUR_J = (SW1 | SW2);   // Enables Pull Up Resistors (makes SWs active low)
}

void SW_reset(void) {  // reset the on-board SWs
  GPIOICR_J |= 0x3;  // Clear interrupt
}

int switch_input(void) { // Set up user inputs
  int button = 0;
  if ((Touch_ReadY() >= 950) & (Touch_ReadY() <= 1200)) {    // If within y range
    if ((Touch_ReadX() >= 800) & (Touch_ReadX() <= 1500)) {  // SW1
      button = 1;
    }
    else if ((Touch_ReadX() >= 1750) & (Touch_ReadX() <= 2000)) {  // SW2
      button = 2;
    }
  }
  // printf("switch: %d\n", button);
  return button; // return the input
}

void Lights_Init(void) {  //set up virtual traffic lights
  unsigned short x1 = 75;                    // Red light x-coordinates
  unsigned short y = 50;                     // lights y-coordinates
  unsigned short radius = 25;                // lights radius
  unsigned short x2 = x1 + (2 * radius) + 25;       // yellow light x-coordinates
  unsigned short x3 = x2 + (2 * radius) + 25;       // green light x-coordinates
  
  // Draw frams for traffic lights in black
  LCD_DrawFilledCircle(x1, y, radius, 0);
  LCD_DrawFilledCircle(x2, y, radius, 0);
  LCD_DrawFilledCircle(x3, y, radius, 0);
}

void Light_On(unsigned short color) { // turn on the assigned light
  // initialized the lights
  Light_Off(RED);
  Light_Off(YELLOW);
  Light_Off(GREEN);
  unsigned short x;     // track the which light by position
  if (color == RED) {   // assign red light
    x = 75;
  }
  else if (color == YELLOW) {   // assign yellow light
    x = 150;  // 75 + 50 + 25
  }
  else if (color == GREEN) {    // assign green light
    x = 225;
  }
  // Draw and filled light according to given color
  LCD_DrawFilledCircle(x, 50, 25, color);
}

void Light_Off(unsigned short color) {  // turn off the assigned light
  unsigned short x;   // track the which light by position
  if (color == RED) { // assign red light
    x = 75;
  }
  else if (color == YELLOW) { // assign yellow light
    x = 150;
  }
  else if (color == GREEN) {  // assign green light
    x = 225;
  }
  // Draw and filled light with black
  LCD_DrawFilledCircle(x, 50, 25, 0);
}

void ADCReadTemp_Init(void) {
  // TASK1B STEP 2: Initialize ADC0 SS3.
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
  
  // 2.6: Disable sample sequencer 3 (SS3)
  ADCACTSS0 &= ~SS3;
  
  // 2.7: Select timer as the trigger for SS3
  ADCEMUX0 |= 0x5000;
  
  // 2.8: Configure ADCSSCTL3 register
  ADCSSCTL3_0 |= 0xC;
  
  // 2.9: Sets sample and hold time to be 128 ADC clocks
  ADCSSTSH3_0 |= 0xA;
  
  // 2.10: Set the SS3 interrupt mask
  ADCIM0 |= SS3;
    
  // 2.11: Set the corresponding bit for ADC0 SS3 in NVIC
  EN0 |= (1 << 17); // 0010 0000 0000 0000 0000
  
  // 2.12: Enable ADC0 SS3
  ADCACTSS0 |= SS3;

}  
   
void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet
  
  RCGCTIMER |= 0x1;
  
  for (int i = 0; i < 2; i++) {}
  
  GPTMCTL &= ~0x1;       // Disables timer
  GPTMCTL |= (1 << 5);   // Sets timer to trigger ADC
  GPTMCFG = 0x0;         // Selects 32-bit mode
  GPTMTAMR |= 0x2;       // Sets register to be in periodic timer mode
  GPTMTAMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down)
  GPTMTAILR = 16000000;  // 16MHz oscillator
  GPTMADCEV |= 0x1;      // Sets type of trigger to be after timer runs out
  GPTMCTL |= 0x1;        // Enables timer
}

void TrafficLightTimer_Init(int ticks) {
  RCGCTIMER |= 0x1;
  GPTMCTL &= ~0x1;       // Disables timer
  GPTMCFG = 0x0;         // Selects 32-bit mode
  GPTMTAMR |= 0x2;       // Sets register to be in periodic timer mode
  GPTMTAMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down)
  GPTMTAILR = 16000000 * ticks;  // 16MHz oscillator * desired seconds
  GPTMCTL |= 0x1;        // Enables timer
}

void timerA_reset(void) {
  GPTMICR |= 0x1;        // Reset timer A
}