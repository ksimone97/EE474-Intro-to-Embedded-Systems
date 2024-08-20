// ______________________ MAIN PROGRAM (main_task1a.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 1 Task 1a
* October 12th, 2023
* This program shows 2 LEDs moving from 4 to 1 in a loop.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab1.h>

int main(void) {
  task1aSetup();
  
  while(1) {
    task1a();
  }
  
  return 0;

}