// *******************************************************************************************************
// File:      hardware.h
// Author:    Aiko Pras
// History:   2024/04/26 AP Version 1.0
// 
// Purpose:   Pin definitions for the TMC 24-Channel AVR64DA64 IO board
// 
// The following generic pin assignments are already made in boards.h of the AP_DCC_Decoder_Core Library:
// rsBusUsart   2;         - PIN_PF0
// swapUsartPin false      - Use the default USART pin
// rsBusRX      PIN_PF2
// dccPin       PIN_PG6
// ackPin       PIN_PG7
// buttonPin    PIN_PG2
// ledPin       PIN_PA7    - This is the DxCore LED Builtin
//                           On board V1.0 this LED is located in the middel of the board
//                           On board V1.3 this LED is located next to the push button
//
// The following Timers are used:
// TCB0: AP_DCC_LIB
// TCB1: Reserved for Servo Lib
// TCB2: DxCore default for millis()
// TCB3: RSBus library
//
// ******************************************************************************************************
#pragma once

// LED pins
#define LED_DCC           PIN_PG1    // indicates valid DCC signal
#define LED_RS            PIN_PG0    // indicates valid RS-Bus signal
#define LED_ACC           PIN_PA2    // an accessory (switch) command for this decoder is received
#define LED_FB            PIN_PA3    // a feedback message is send
#define LED_TEST          PIN_PF5

// Monitoring Pins
#define MON_TXD           PIN_PA0    // Serial
#define MON_RXD           PIN_PA1    // 

// The DIP switches  that determine whether a certain POORT is input (MELDEN) or output (SCHAKELEN)
#define DIP_SWITCH_1      PIN_PA4    // Port 1 (D) is input (value = 0) or output (value = 1)
#define DIP_SWITCH_2      PIN_PA5    // Port 2 (C) is input (value = 0) or output (value = 1)
#define DIP_SWITCH_3      PIN_PA6    // Port 3 (B) is input (value = 0) or output (value = 1)
#define SCHAKELEN         0          // Possible DIP switch value
#define MELDEN            1          // Possible DIP switch value

// The 24 pins of the 25 pin SUBD connector are connected to the following AVR128DA48 ports:
// 1..8 = PORTD, 9..16 = PORTC and 17..24 = PORTB. 
// To avoid confusion with names, we will use POORT0 for PORTD, POORT1 for POTC and POORT2 for PORTB.
#define POORT0_IN_REGISTER  PORTD.IN
#define POORT1_IN_REGISTER  PORTC.IN
#define POORT2_IN_REGISTER  PORTB.IN

#define POORT0_IS_MELDEN    PORTD.DIR = 0x00
#define POORT1_IS_MELDEN    PORTC.DIR = 0x00
#define POORT2_IS_MELDEN    PORTB.DIR = 0x00
#define POORT0_IS_SCHAKELEN PORTD.DIR = 0xFF
#define POORT1_IS_SCHAKELEN PORTC.DIR = 0xFF
#define POORT2_IS_SCHAKELEN PORTB.DIR = 0xFF


// Map the 24 pins of the 25 pin SUBD connector to the AVR output pins
// Note that we could have made a more iniuitive mapping, 
// but that would have made PCB design more difficult
#define POORT0_1  PIN_PD7
#define POORT0_2  PIN_PD6
#define POORT0_3  PIN_PD5
#define POORT0_4  PIN_PD4
#define POORT0_5  PIN_PD3
#define POORT0_6  PIN_PD2
#define POORT0_7  PIN_PD1
#define POORT0_8  PIN_PD0
#define POORT1_1  PIN_PC7
#define POORT1_2  PIN_PC6
#define POORT1_3  PIN_PC5
#define POORT1_4  PIN_PC4
#define POORT1_5  PIN_PC3
#define POORT1_6  PIN_PC2
#define POORT1_7  PIN_PC1
#define POORT1_8  PIN_PC0
#define POORT2_1  PIN_PB7
#define POORT2_2  PIN_PB6
#define POORT2_3  PIN_PB5
#define POORT2_4  PIN_PB4
#define POORT2_5  PIN_PB3
#define POORT2_6  PIN_PB2
#define POORT2_7  PIN_PB1
#define POORT2_8  PIN_PB0


class ledClass {
  public:
    void init();
};


// *******************************************************************************************************
// Definition of the LED object, which is declared in hardware.cpp but used elsewhere 
extern ledClass leds;
