// _________ Lab 5 main (Lab5.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 5
* December 7th, 2023
* This program shows one LED dimming in a loop using a PWM.
*/

#include "lab5.h"
#include <stdint.h>
#include "Lab5_Inits.h"
#include <stdio.h>

int main(void) {
  TimerA_Init();
  PWM_Init();
  
  while (1) {    
    LED_On();
    LED_Off();
  } 
  
  return 0;
}

