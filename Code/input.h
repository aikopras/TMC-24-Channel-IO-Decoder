// *******************************************************************************************************
// File:      input.h
// Author:    Aiko Pras
// History:   2024/05/05 AP Version 1.0
// 
// Purpose:   Read the values of all input pins
// , 
// We perform some input shaping to limit the effect of interference and bad rail contacts:
// - if a pin level changes from LOW to HIGH, we take some additional samples before we decide 
//   that the result value should also become HIGH.
//   In this way we expect to filter small spikes that may result from interference.
//   CV33 (Min_1Samples) determines how many samples we take. The default value is 3.
// - if a pin value changes from HIGH to LOW, we wait a certain time before we decide that the
//   result value should also become LOW.
//   In this way we expect to to filter short bad contact between rails and engine.
//   Only if the pin value remains LOW for a longer period, we change the result value to LOW.
//   CV34 (Min_0Samples) determines how many samples we will wait before we change the result to LOW.
// The main sketch determines the time between consequtive samples. A reasonable value is 10 ms.
//
// *******************************************************************************************************
#pragma once

#include <Arduino.h>                  // For general definitions
#include <AP_DCC_Decoder_Core.h>      // To include all objects, such as dcc, accCmd, etc.


class portClass {
  public: 
    void init();
    void check(uint8_t i, uint8_t inRegister);

    struct {
      uint8_t pinHistory;             // store 8 consequtive samples, to later filter spikes
      uint8_t delayBeforeOff;         // number of sample before the result value becomes 0
      boolean result;                 // if the pin is reliably HIGH or LOW
    } pin[8];                         // we have 8 input pins.
    
  private:
    uint8_t MinSamplesMask;           // Mask which we create in init() from CV33 (Min_1Samples)
    uint8_t maxDelayBeforeOff;        // Initialised from CV34. Number of samples 
};

extern portClass port[3];             // we have three ports (0, 1 & 2)
