// _________ Lab 4 Task 2a main (Lab4_Task2a.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 4 Task 2a
* November 30th, 2023
* This program builds off of Lab 2 Task 1b. It creates a virtual traffic light controller 
*   with two buttons, one acting as power and another signalling a pedestrian 
*   being present. When the power is off, no LEDs are on. When the power is on 
*   and no buttons are pressed, the LEDs switch from green to red (starting with red). 
*   When the pedestrian button is held for 2 seconds, the LEDs go from green to yellow 
*   to red (if held when in Go state) or stays red (if held when in Stop state). The
*   transitions take 5 seconds and only button presses held for 2 seconds are
*   recognized. Presses that aren't held result in delays in each state.
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
  LCD_Init();                 // set up LCD display
  LCD_ColorFill(Color4[15]);  // light up LCD  
  Buttons_Init();             // Draws the buttons on the LCD
  Touch_Init();               // set up touch functions
  Lights_Init();              // set up LED
  
  int button = switch_input();  // What button was pressed
  int countPow = 0; // initialize POWER BUTTON counter
  int countPed = 0; // initialize PEDESTRIAN BUTTON counter

  while(1) {
    /*
    bottom right 2400, 900

    SW1 top left (750, 1250?), bottom right (1500, 900)

    SW2 top left (1750, 1250?) bottom right (2000, 900)

    */

    // printf("x: %d, y: %d\n", Touch_ReadX(), Touch_ReadY());
    
    TrafficLight(&countPow, &countPed); // timed traffic light
  }
  return 0;
}

