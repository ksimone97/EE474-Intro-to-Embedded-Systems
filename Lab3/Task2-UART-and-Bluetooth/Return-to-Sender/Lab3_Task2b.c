// _________ LAB 3 Task 2b main (Lab3_Task2b.c) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 3 Task 2b
* November 16th, 2023
* This program receives input from the computer via Bluetooth communication from
*   a PuTTY terminal and echoes that input back to the terminal as an output.
*/

#include <stdint.h>
#include "Lab3_Inits.h"
#include "lab3.h"

int main(void) {
  UART3_Init();

  while(1) {
    char userInput;
    
    if (UARTFR3 & (1 << 6)) {  // Only start if the receiver is  full
      userInput = (UARTDR3 & 0xFF);  // Read just the char data
      
      while ((UARTFR3 & (1 << 3)) != 0) {}  // Wait while transmitter is busy
      UARTDR3 |= userInput;  // Transmit the data back to the PuTTY terminal
    }
  }
  return 0;
}
