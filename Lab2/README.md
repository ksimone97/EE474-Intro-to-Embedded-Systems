# Lab 2: General-Purpose Timers and Interrupts
The purpose of this lab is to delay CPU operation in the programs made in Lab 1, reducing unnecessary CPU execution. This will be done 2 different ways, via implementing timers and interrupts. 

## Task 1: Timers
### 1a: Sequencial LEDs
This task was to modify Lab 1's Task 1a (to turn on and off all of the LEDs in a sequential pattern) by adding timers.
### 1b: Traffic Controller
This task was to modify Lab 1's Task 2 (to create a program that turns on various colored LEDs using the user switches (buttons), turning on LED1 when SW1 is pressed and LED2 when SW2 is pressed) by using timers to require the user to hold a button for at least 2 seconds in order for any button press to be registered. It also times the transition to/from each state (color).

## Task 2: Interrupts
### 2a: Sequencial LEDs
This task was to repeat Task 1a, but instead of polling the timers, we use interrupts.
### 2b: GPIO Input
This task was to program a blinking LED1 at a rate of 1Hz and use SW1 and SW2 buttons to interrupt the program. When SW1 is pressed, the timer will stop counting down, LED1 will shut off, and LED2 will turn on. It will not return to the original pattern of LED1 blinking until SW2 is pressed.
### 2c: Traffic Controller
This task was to repeat Task 1b using interrupts instead of polling.

## **Shared Files:**
* lab2.h - All
* timer.c - All
* button.c - 1b, 2c
* LED.c - 1b, 2c