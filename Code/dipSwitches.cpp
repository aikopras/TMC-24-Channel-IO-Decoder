// *******************************************************************************************************
// File:      dipSwitches.cpp
// Author:    Aiko Pras
// History:   2024/04/27 AP Version 1.0
// 
// Purpose:   Read the DIP switches and (re)configure the outputs if needed 
// 
// *******************************************************************************************************
#include <Arduino.h>                  // For general definitions
#include "hardware.h"                 // Pin assignments and #defines
#include "dipSwitches.h"

dipSwitchClass dipSwitches;           // Instantiate the object vor the 3 DIP switches


void dipSwitchClass::init() {
  // The three input pins must have pull-ups
  pinMode(DIP_SWITCH_1, INPUT_PULLUP);   // initialise as input (MELDEN)
  pinMode(DIP_SWITCH_2, INPUT_PULLUP);
  pinMode(DIP_SWITCH_3, INPUT_PULLUP);
  dip1setting = MELDEN;                  // initialise as MELDEN (input)
  dip2setting = MELDEN;
  dip3setting = MELDEN;
  POORT0_IS_MELDEN;                      // set the DIR register of the associated AVR PORT
  POORT1_IS_MELDEN;
  POORT2_IS_MELDEN;
  // Check each of the three DIP switches 
  check();
}


void dipSwitchClass::check() {
  uint8_t newValue;
  // Check DIP switch 1
  newValue = digitalReadFast(DIP_SWITCH_1);  
  if (newValue != dip1setting) {
    dip1setting = newValue;    // set the boolean flag to facilitate detection of changes
    if (dip1setting == MELDEN) {
      Serial.println("DIP switch 1: Melden");
      POORT0_IS_MELDEN;        // set the DIR register of the associated AVR PORT
    }
    else {
      Serial.println("DIP switch 1: Schakelen");
      POORT0_IS_SCHAKELEN;     // set the DIR register of the associated AVR PORT
    }
  }
  // Check DIP switch 2
  newValue = digitalReadFast(DIP_SWITCH_2);  
  if (newValue != dip2setting) {
    dip2setting = newValue;
    if (dip2setting == MELDEN) {
      Serial.println("DIP switch 2: Melden");
      POORT1_IS_MELDEN;        // set the DIR register of the associated AVR PORT
    }
    else {
      Serial.println("DIP switch 2: Schakelen");
      POORT1_IS_SCHAKELEN;
    }
  }
  // Check DIP switch 3
  newValue = digitalReadFast(DIP_SWITCH_3);  
  if (newValue != dip3setting) {
    dip3setting = newValue;
    if (dip3setting == MELDEN) {
      Serial.println("DIP switch 3: Melden");
      POORT2_IS_MELDEN;        // set the DIR register of the associated AVR PORT
    }
    else {
      Serial.println("DIP switch 3: Schakelen");
      POORT2_IS_SCHAKELEN;
    }
  }
}

/*
void dipSwitchClass::print() {
  if (digitalReadFast(DIP_SWITCH_1)) {Serial.println("DIP swich 1 = Melden");}
  else Serial.println("DIP swich 1 = Schakelen");
  if (digitalReadFast(DIP_SWITCH_2)) {Serial.println("DIP swich 2 = Melden");}
  else Serial.println("DIP swich 2 = Schakelen");
  if (digitalReadFast(DIP_SWITCH_3)) {Serial.println("DIP swich 3 = Melden");}
  else Serial.println("DIP swich 3 = Schakelen");
}
*/
