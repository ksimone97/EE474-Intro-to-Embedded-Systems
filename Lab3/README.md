# Lab 3: ADC, UART, and Bluetooth
The purpose of this lab is to experiment with using the board’s Analog to Digital Converters (ADCs) to gather sensor data as well as the board’s Universal Asynchronous Receiver/Transmitters (UARTs) to serially transmit data through both wired and wireless communication.

## Task 1: Analog to Digital Readings
### 1a: Potentiometer-Controlled LEDs
This task was to measure the voltage of the potentiometer's middle pin, convert it to the resistance of the potentiometer, then use the on-board LEDs to represent the resistance.
### 1b: Displaying Board Temperature
This task was to read the temperature data from the board's internal temperature sensor and print the temperature to the terminal. The two onboard switches were also programmed to change the system clock frequency with the provided PLL driver, affecting the board's internal temperature.

## Task 2: UART and Bluetooth
### 2a: Sending Temperature Readings via UART
This task was to use UART serial communication to print the temperature readings from Task 1b to the terminal in PuTTY.
### 2b: The "Return-to-Sender" Function
This task was to create a new program that receives a single character via UART and immediately transmits back the character that it receives (a “Return-to-Sender” function) using Bluetooth communication. The PuTTY interface was used to demonstrate this program.

## **Shared Files:**
* cstartup_M.c - All
* lab3.h - All
* PLL_Header.h - All
* Lab3_Inits.h - All
* Lab3_Inits.c - All