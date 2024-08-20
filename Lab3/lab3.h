// _________ HEADER FILE (lab3.h) _________
/*
* Kiana Peterson & Nattapon "Genie" Oonlamom
* Lab 3
* November 16th, 2023
* This header has a collection of register definitions from labs 1-3.
*/

#ifndef __LAB3_H__
#define __LAB3_H__

// Enables the clock and ADC clock
#define RCGCGPIO (*((volatile uint32_t*)0x400FE608))
#define RCGCADC (*((volatile uint32_t*)0x400FE638))
#define RCGCUART (*((volatile uint32_t*)0x400FE618))


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


// Defines the register addresses for timers 0A and 0B
#define RCGCTIMER (*((volatile uint32_t*)0x400FE604))
#define GPTMCTL (*((volatile uint32_t*)0x4003000C))
#define GPTMCFG (*((volatile uint32_t*)0x40030000))
#define GPTMTAMR (*((volatile uint32_t*)0x40030004))
#define GPTMTBMR (*((volatile uint32_t*)0x40030008))
#define GPTMTAILR (*((volatile uint32_t*)0x40030028))
#define GPTMTBILR (*((volatile uint32_t*)0x4003002C))
#define GPTMIMR (*((volatile uint32_t*)0x40030018))
#define GPTMRIS (*((volatile uint32_t*)0x4003001C))
#define GPTMICR (*((volatile uint32_t*)0x40030024))
#define GPTMADCEV (*((volatile uint32_t*)0x40030070))


// Defines the register addresses for configuring interrupts
#define EN0 (*((volatile uint32_t*)0xE000E100))
#define EN1 (*((volatile uint32_t*)0xE000E104))
#define PRI1 (*((volatile uint32_t*)0xE000E404))
#define PRI4 (*((volatile uint32_t*)0xE000E410))
#define PRI5 (*((volatile uint32_t*)0xE000E414))
#define PRI12 (*((volatile uint32_t*)0xE000E430))


// Defines the register addresses for Port F GPIOs
#define GPIODIR_F (*((volatile uint32_t*)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t*)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t*)0x4005D3FC))

// Defines the register addresses for Port N GPIOs
#define GPIODIR_N (*((volatile uint32_t*)0x40064400))
#define GPIODEN_N (*((volatile uint32_t*)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t*)0x400643FC))

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

// Defines the register addresses for Port A GPIOs
#define GPIOAFSEL_A (*((volatile uint32_t*)0x40058420))
#define GPIODEN_A (*((volatile uint32_t*)0x4005851C))
#define GPIOPCTL_A (*((volatile uint32_t*)0x4005852C))


#endif // __LAB3_H__