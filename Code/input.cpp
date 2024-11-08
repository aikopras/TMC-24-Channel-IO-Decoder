// *******************************************************************************************************
// File:      input.cpp
// Author:    Aiko Pras
// History:   2024/05/05 AP Version 1.0
// 
// Purpose:   Handling the feedback signals
// 
// *******************************************************************************************************
#include <Arduino.h>                  // For general definitions
#include <AP_DCC_Decoder_Core.h>      // To include all objects, such as dcc, accCmd, etc.
#include "hardware.h"                 // Pin assignments and #defines
#include "dipSwitches.h"              // The three switches that determine MELDEN or SCHAKELEN
#include "input.h"

portClass port[3];


void portClass::init() {
  // STEP 1: Read the minimum number of positive samples that need to be the same, before the signal
  // is considered to be stable. Ensure validity and use this number to calculate a mask
  uint8_t minSamples  = cvValues.read(Min_1Samples);
  if (minSamples == 0) {minSamples = 1;}
  if (minSamples > 8 ) {minSamples = 8;}  
  MinSamplesMask = 1;
  for (uint8_t i = 1; i < minSamples; i++) {MinSamplesMask = MinSamplesMask * 2 + 1;}
  // STEP 2: Read the CV for delayOff 
  maxDelayBeforeOff = cvValues.read(Min_0Samples);
  // STEP 3: Initialise for each of the three ports the associated 8 pins
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      port[i].pin[j].pinHistory = 0;
      port[i].pin[j].delayBeforeOff = 0;
      port[i].pin[j].result = 0;
    }
  }
}


void portClass::check(uint8_t i, uint8_t inRegister) {
  // note: i = port (0..2), j = pin (0..7)
  // STEP 1: check the value for each individual pin 
  for (uint8_t j = 0; j <= 7; j++) {
    // STEP 1: determine the value of the input pin
    uint8_t pinValue = bitRead(inRegister, j);
    // STEP 2: update the pinHistory
    // Shift all bits to the left and add the new pin value to the right 
    port[i].pin[j].pinHistory = (port[i].pin[j].pinHistory << 1) + pinValue;    
    // STEP 3: update delayBeforeOff
    if (pinValue) port[i].pin[j].delayBeforeOff = maxDelayBeforeOff;
      else if (port[i].pin[j].delayBeforeOff > 0) port[i].pin[j].delayBeforeOff--;      
    // STEP 4 Change the result value, if needed 
    if (port[i].pin[j].result == 0) {
      // Should the result value change from 0 to 1?
      // In that case, the pinHistory should have been consistently high for multiple samples
      // We use MinSamplesMask to isolate the number of samples that should be considered
      // If the masked value is the same as the mask itself, all samples are 1, thus "on" is stable
      uint8_t relevantSamples = port[i].pin[j].pinHistory & MinSamplesMask; // bitwise AND (mask)
      if (relevantSamples == MinSamplesMask) port[i].pin[j].result = 1;
    }
    else {
    // Should the result value change from 1 to 0?
    // In that case, the delayBeforeOff time should have become 0
    if (port[i].pin[j].delayBeforeOff == 0) port[i].pin[j].result = 0;
    }      
  }
}
