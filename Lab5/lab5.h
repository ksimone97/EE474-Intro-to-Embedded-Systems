// _________ HEADER FILE (lab5.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 5
* December 7th, 2023
* This header has a collection of register definitions from labs 1-5.
*/

#ifndef __LAB5_H__
#define __LAB5_H__

// Defines the register addresses for the various clocks
#define RCGCGPIO (*((volatile uint32_t*)0x400FE608))
#define RCGCTIMER (*((volatile uint32_t*)0x400FE604))
#define RCGCADC (*((volatile uint32_t*)0x400FE638))
#define RCGCUART (*((volatile uint32_t*)0x400FE618))
#define RCGCPWM (*((volatile uint32_t*)0x400FE640))


// Defines the register addresses for the ADC
#define ADCCC0 (*((volatile uint32_t*)0x40038FC8))
#define ADCACTSS0 (*((volatile uint32_t*)0x40038000))
#define ADCEMUX0 (*((volatile uint32_t*)0x40038014))
#define ADCSSMUX3_0 (*((volatile uint32_t*)0x400380A0))
#define ADCSSCTL3_0 (*((volatile uint32_t*)0x400380A4))
#define ADCRIS0 (*((volatile uint32_t*)0x40038004))
#define ADCIM0 (*((volatile uint32_t*)0x40038008))
#define ADCISC0 (*((volatile uint32_t*)0x4003800C))
#define ADCSSFIFO3 (*((volatile uint32_t*)0x400380A8))
#define ADCSSTSH3_0 (*((volatile uint32_t*)0x400380BC))


// Defines the register addresses for the UART0
#define UARTCTL0 (*((volatile uint32_t*)0x4000C030))
#define UARTIBRD0 (*((volatile uint32_t*)0x4000C024))
#define UARTFBRD0 (*((volatile uint32_t*)0x4000C028))
#define UARTLCRH0 (*((volatile uint32_t*)0x4000C02C))
#define UARTCC0 (*((volatile uint32_t*)0x4000CFC8))
#define UARTDR0 (*((volatile uint32_t*)0x4000C000))
#define UARTFR0 (*((volatile uint32_t*)0x4000C018))

// Defines the register addresses for the UART3
#define UARTCTL3 (*((volatile uint32_t*)0x4000F030))
#define UARTIBRD3 (*((volatile uint32_t*)0x4000F024))
#define UARTFBRD3 (*((volatile uint32_t*)0x4000F028)) 
#define UARTLCRH3 (*((volatile uint32_t*)0x4000F02C))
#define UARTCC3 (*((volatile uint32_t*)0x4000FFC8))
#define UARTDR3 (*((volatile uint32_t*)0x4000F000))
#define UARTFR3 (*((volatile uint32_t*)0x4000F018))

// Defines the register addresses for PWM
#define PWMCC (*((volatile uint32_t*)0x40028FC8))
#define PWMENABLE (*((volatile uint32_t*)0x40028008))
#define PWMCTL0 (*((volatile uint32_t*)0x40028040))
#define PWMGENA0 (*((volatile uint32_t*)0x40028060))
#define PWMLOAD0 (*((volatile uint32_t*)0x40028050))
#define PWMCMPA0 (*((volatile uint32_t*)0x40028058))

// Defines the register addresses for timers 0A and 0B
#define GPTMCTL (*((volatile uint32_t*)0x4003000C))
#define GPTMCFG (*((volatile uint32_t*)0x40030000))
#define GPTMTAMR (*((volatile uint32_t*)0x40030004))
#define GPTMTBMR (*((volatile uint32_t*)0x40030008))
#define GPTMTAILR (*((volatile uint32_t*)0x40030028))
#define GPTMTBILR (*((volatile uint32_t*)0x4003002C))
#define GPTMIMR (*((volatile uint32_t*)0x40030018))
#define GPTMRIS (*((volatile uint32_t*)0x4003001C)
#define GPTMICR (*((volatile uint32_t*)0x40030024))
#define GPTMADCEV (*((volatile uint32_t*)0x40030070))

// Defines the register addresses for configuring interrupts
#define EN0 (*((volatile uint32_t*)0xE000E100))
#define EN1 (*((volatile uint32_t*)0xE000E104))
#define PRI1 (*((volatile uint32_t*)0xE000E404))
#define PRI4 (*((volatile uint32_t*)0xE000E410))
#define PRI5 (*((volatile uint32_t*)0xE000E414))
#define PRI12 (*((volatile uint32_t*)0xE000E430))


// Defines the register addresses for Port A GPIOs
#define GPIOAFSEL_A (*((volatile uint32_t*)0x40058420))
#define GPIODEN_A (*((volatile uint32_t*)0x4005851C))
#define GPIOPCTL_A (*((volatile uint32_t*)0x4005852C))

// Defines the register addresses for Port D GPIOs
#define GPIODIR_D (*((volatile uint32_t*)0x4005B400))
#define GPIOAFSEL_D (*((volatile uint32_t*)0x4005B420))
#define GPIODEN_D (*((volatile uint32_t*)0x4005B51C))

#define GPIOIS_D (*((volatile uint32_t*)0x4005B404))
#define GPIOIBE_D (*((volatile uint32_t*)0x4005B408))
#define GPIOIVE_D (*((volatile uint32_t*)0x4005B40C))
#define GPIOIM_D (*((volatile uint32_t*)0x4005B410))
#define GPIORIS_D (*((volatile uint32_t*)0x4005B414))
#define GPIOICR_D (*((volatile uint32_t*)0x4005B41C))

// Defines the register addresses for Port E GPIOs
#define GPIOAMSEL_E (*((volatile uint32_t*)0x4005C528))
#define GPIODIR_E (*((volatile uint32_t*)0x4005C400))
#define GPIODEN_E (*((volatile uint32_t*)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t*)0x4005C420))
#define GPIODATA_E (*((volatile uint32_t*)0x4005C3FC))

#define GPIOIS_E (*((volatile uint32_t*)0x4005C404))
#define GPIOIBE_E (*((volatile uint32_t*)0x4005C408))
#define GPIOIVE_E (*((volatile uint32_t*)0x4005C40C))
#define GPIOIM_E (*((volatile uint32_t*)0x4005C410))
#define GPIORIS_E (*((volatile uint32_t*)0x4005C414))
#define GPIOICR_E (*((volatile uint32_t*)0x4005C41C))

// Defines the register addresses for Port F GPIOs
#define GPIODIR_F (*((volatile uint32_t*)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t*)0x4005D51C))
#define GPIOAFSEL_F (*((volatile uint32_t*)0x4005D420))
#define GPIOPCTL_F (*((volatile uint32_t*)0x4005D52C))
#define GPIODATA_F (*((volatile uint32_t*)0x4005D3FC))

// Defines the register addresses for Port J GPIOs
#define GPIODIR_J (*((volatile uint32_t*)0x40060400))
#define GPIODEN_J (*((volatile uint32_t*)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t*)0x400603FC))
#define GPIOPUR_J (*((volatile uint32_t*)0x40060510))

#define GPIOIS_J (*((volatile uint32_t*)0x40060404))
#define GPIOIBE_J (*((volatile uint32_t*)0x40060408))
#define GPIOIVE_J (*((volatile uint32_t*)0x4006040C))
#define GPIOIM_J (*((volatile uint32_t*)0x40060410))
#define GPIORIS_J (*((volatile uint32_t*)0x40060414))
#define GPIOICR_J (*((volatile uint32_t*)0x4006041C))

// Defines the register addresses for Port K GPIOs
#define GPIODIR_K (*((volatile uint32_t*)0x40061400))
#define GPIOAFSEL_K (*((volatile uint32_t*)0x40061420))
#define GPIODEN_K (*((volatile uint32_t*)0x4006151C))

// Defines the register addresses for Port M GPIOs
#define GPIODIR_M (*((volatile uint32_t*)0x40063400))
#define GPIOAFSEL_M (*((volatile uint32_t*)0x40063420))
#define GPIODEN_M (*((volatile uint32_t*)0x4006351C))

// Defines the register addresses for Port N GPIOs
#define GPIODIR_N (*((volatile uint32_t*)0x40064400))
#define GPIOAFSEL_N (*((volatile uint32_t*)0x40064420))
#define GPIODEN_N (*((volatile uint32_t*)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t*)0x400643FC))

// Defines the register addresses for Port P GPIOs
#define GPIODIR_P (*((volatile uint32_t*)0x40065400))
#define GPIOAFSEL_P (*((volatile uint32_t*)0x40065420))
#define GPIODEN_P (*((volatile uint32_t*)0x4006551C))

// Defines the register addresses for Port Q GPIOs
#define GPIODIR_Q (*((volatile uint32_t*)0x40066400))
#define GPIOAFSEL_Q (*((volatile uint32_t*)0x40066420))
#define GPIODEN_Q (*((volatile uint32_t*)0x4006651C))

#endif // __LAB5_H__