// _________ LAB 4 Task 1a main (Lab4_Task1a.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 4 Task 1a
* November 30th, 2023
* This program filled LCD screen with color.
*/
#include "SSD2119_Display.h"
#include "tm4c1294ncpdt.h"
#include "lab4.h"

void main(void) {
  LCD_Init();   // Initialize LCD driver
  LCD_ColorFill(Color4[6]);   // fill in the screen with brown
}