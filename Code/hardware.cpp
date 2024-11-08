// *******************************************************************************************************
// File:      hardware.cpp
// Author:    Aiko Pras
// History:   2024/04/26 AP Version 1.0
// 
// Purpose:   To initialise the LEDs and associated timers
//
// ******************************************************************************************************
#include <Arduino.h>                  // For general definitions
#include <AP_DCC_Decoder_Core.h>      // To include all objects, such as dcc, accCmd, etc.
#include "hardware.h"


void ledClass::init() {
  pinMode(LED_DCC, OUTPUT);
  digitalWrite(LED_DCC, LOW);        // indicates valid DCC signal
  pinMode(LED_RS, OUTPUT);
  digitalWrite(LED_RS, LOW);         // indicates valid RS-Bus signal
  pinMode(LED_ACC, OUTPUT);
  digitalWrite(LED_ACC, LOW);        // an accessory (switch) command for this decoder is received
  pinMode(LED_FB, OUTPUT);
  digitalWrite(LED_FB, LOW);         // a feedback message is send
  pinMode(LED_TEST, OUTPUT);
  digitalWrite(LED_TEST, LOW);       // may be used for debugging purposes
};
