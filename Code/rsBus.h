// *******************************************************************************************************
// File:      RSBus.h
// Author:    Aiko Pras
// History:   2024/05/09 AP Version 1.0
// 
// Purpose:   Sending RS-Bus feedback messages
// 
// *******************************************************************************************************
#pragma once


// To initialise the three RS-Bus addresses
class CommonRSBusClass {
  public:
    void init();
    void checkLed();
    void test(uint8_t busNr);              // TODO: May be removed
};


// For an individual RS-Bus connection
class RSBusClass {
  public:
    void check(uint8_t i);                 // i = 0..2 and represents the number of the input port

    RSbusConnection rsbus;
    uint8_t lowNibble;
    uint8_t highNibble;
};


extern CommonRSBusClass RSCommon;
extern RSBusClass feedback[3];             // we have three RS-Bus connections (0..2)
