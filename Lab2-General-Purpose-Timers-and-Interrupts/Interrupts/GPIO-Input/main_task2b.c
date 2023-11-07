// ______________________ MAIN PROGRAM (main_task2b.c) ______________________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2 Task 2b
* November 2nd, 2023
* This program shows LED1 flashing every second (lasting for a second). If SW1
*   is pressed, LED1 stops flashing (the timer also stops counting down) and 
*   LED2 turns on. When SW2 is pressed, the timer resumes, LED1 starts flashing
*   again, and LED2 turns off.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

int main(void) {
  GPIO_init();
  task2Timer_init();
  
  while (1) {}
  
  return 0;

}

void Timer0A_Handler() {
  timerA_reset();
  
  // Blinks LED 1
  GPIODATA_N ^= LED1;
}

void GPIOJ_Handler () {
  SW_reset();
  
  // If SW1 is pressed, stops flashing LED1 and turns on LED2
  if (GPIODATA_J == SW1) {
    GPTMCTL &= ~0x1;  // Disables timer (no timed interrupts)
    GPIODATA_N = LED2;
  }
  
  // If SW2 is pressed, goes back to flashing LED1 and turns off LED2
  else if (GPIODATA_J == SW2) {
    GPTMCTL |= 0x1;  // Enables timer (interrupts every second)
    GPIODATA_N &= ~LED2;
  }
}