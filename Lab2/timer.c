// _________ Lab 2 Timers Setup Program (.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 2
* November 2nd, 2023
* This program sets up periodic timers 0A and 0B with or without interrupts.
*/

#include <stdint.h>
#include <stdio.h>
#include <lab2.h>

void task1Timer_init(int ticks) {
  RCGCTIMER |= 0x1;
  GPTMCTL &= ~0x1;       // Disables timer
  GPTMCFG = 0x0;         // Selects 32-bit mode
  GPTMTAMR |= 0x2;       // Sets register to be in periodic timer mode
  GPTMTAMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down)
  GPTMTAILR = 16000000 * ticks;  // 16MHz oscillator * desired seconds
  GPTMCTL |= 0x1;        // Enables timer
}

void task2Timer_init(void) {  
  RCGCTIMER |= 0x1;
  GPTMCTL &= ~0x1;       // Disables timer
  GPTMCFG = 0x0;         // Selects 32-bit mode
  GPTMTAMR |= 0x2;       // Sets register to be in periodic timer mode
  GPTMTAMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down)
  GPTMTAILR = 16000000;  // 16MHz oscillator
  GPTMIMR |= 0x1;        // Enables interrupt mask
  EN0 |= (1 << 19);      // 1000 0000 0000 0000 0000
  GPTMCTL |= 0x1;        // Enables timer
}

void task2cTimer_init(void) {  
  RCGCTIMER |= 0x1;
  GPTMCTL &= ~0x101;     // Disables timers A and B
  GPTMCFG = 0x0;         // Selects 32-bit mode
  
  GPTMTAMR |= 0x2;       // Sets register to be in periodic timer mode (timer A)
  GPTMTBMR |= 0x2;       // Sets register to be in periodic timer mode (timer B)

  GPTMTAMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down) (timer A)
  GPTMTBMR &= ~0x10;     // Sets TACDIR bit to be 0 (count down) (timer B)

  GPTMTAILR = 80000000;  // 16MHz oscillator Timer A = 5 seconds
  GPTMTBILR = 32000000;  // 16MHz oscillator Timer B = 2 seconds

  GPTMIMR |= 0x101;      // Unmask interrupts
  EN0 |= (1 << 19);      // Enables interrupt
  EN0 |= (1 << 20);      // Enables interrupt
  PRI4 |= (1 << 30);     // Sets priority level for Interrupt 19 to be 2
  PRI5 &= ~0xE0;         // Sets priority level for Interrupt 20 to be 0

  GPTMCTL |= 0x001;      // Enables timer A
}

void timerA_reset(void) {
  GPTMICR |= 0x1;        // Reset timer A
}

void timerB_reset(void) {
  GPTMICR |= 0x100;      // Reset timer B
}

void delay() {
  while ((GPTMRIS & 0x1) == 0) {}  // Polls GPTMRIS for timer A flag
  timerA_reset();
}