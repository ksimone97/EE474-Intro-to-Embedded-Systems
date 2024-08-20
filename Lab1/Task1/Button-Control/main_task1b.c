// ______________________ MAIN PROGRAM (main_task1b.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 1b
* October 12th, 2023
* This program lights up LED1 when SW1 is pressed and LED2 when SW2 is pressed.
*/

#include <stdint.h>
#include <stdio.h>
#include <Lab1Task1.h>

void main(void) {
  task1bSetup();
  
  while(1) {
    task1b();
  }
  
}