# Lab 4: LCD Display, Touch Screen, and RTOS
The purpose of this lab is to interface the TM4C LaunchPad to display graphics and use virtual buttons on a touch-screen LCD. Once that is complete, the purpose is to build upon that to compare implementing the FSM for a touch-screen Traffic Light via bare-metal programming versus using the RTOS.

## Task 1: LCD Driver
### 1a: Complete LCD Driver
This task was to get the LCD driver and display working. 
### 1b: Displaying Board Temperature
This task was to change Lab 3's Task 1b so that it prints the temperature on the LCD display. It should still read the temperature data from the board's internal temperature sensor and utilize the two onboard switches to change the system clock frequency.
### 1c: Resistive Touch Screen
This task was to expand on Task 1b by creating two virtual buttons on the touch-screen display, replacing the on-board physical buttons. 

## Task 2: Bare-Metal Programming vs Real-Time Operating System
### 2a: Bare-Metal Programming Virtual Traffic Light
This task was to recreate the Traffic Light from Lab 2 virtually, instead of using external LEDs and buttons.
### 2b: RTOS Virtual Traffic Light
This task was to repeat Task 2a using FreeRTOS instead of bare-metal programming.

## **Shared Files:**
* cstartup_M.c - All
* lab4.h - All
* PLL_Header.h - All
* Lab4_Inits.h - All
* Lab4_Inits.c - All
* SSD2119_Display.c - All