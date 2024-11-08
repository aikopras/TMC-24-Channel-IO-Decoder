// *******************************************************************************************************
// File:      RSBus.cpp
// Author:    Aiko Pras
// History:   2024/05/09 AP Version 1.0
// 
// Purpose:   Sending RS-Bus feedback messages
//            Reads the pin values and sends a feedback message once a pin value changed.
// 
// *******************************************************************************************************
#include <AP_DCC_Decoder_Core.h>      // To include all objects, such as dcc, accCmd, etc.
#include "hardware.h"                 // Pin assignments and #defines
#include "myDefaults.h"               // Default values for this specific board
#include "dipSwitches.h"              // The three switches that determine MELDEN or SCHAKELEN
#include "input.h"                    // To handle all IO input pins
#include "rsBus.h"


CommonRSBusClass RSCommon;            // Object to initialises the RS-Bus addresses
RSBusClass feedback[3];               // Object for the three RS-Bus connections 
DccTimer RSLedTimer;                  // To switch the LED off that signals the transmission of a feedback message

extern RSbusHardware rsbusHardware;  // This object is defined in rs_bus.cpp


// *******************************************************************************************************
void CommonRSBusClass::init() {
  uint8_t firstRSAddress = cvValues.read(myRSAddr);      // 1.. 127
  if (firstRSAddress <= 125) {
    feedback[0].rsbus.address = firstRSAddress;
    feedback[1].rsbus.address = firstRSAddress + 1;
    feedback[2].rsbus.address = firstRSAddress + 2;
  }
}


void CommonRSBusClass::checkLed() {
  if (rsbusHardware.rsSignalIsOK) digitalWrite(LED_RS, 1); 
  else digitalWrite(LED_RS, 0);    // No valid RS-Bus signal
}


// *******************************************************************************************************
void RSBusClass::check(uint8_t i) {
  // i is the input port (0..2) 
  boolean sendLowNibble = false;
  boolean sendHighNibble = false;
  //  
  // STEP 1: read the 8 pin values of this port, and update (if needed)
  // the lowNibble and highNibble variable. Set a flag if such variable changes
  uint8_t newNibble = 0;
  // Low nibble first
  for (uint8_t j = 4; j < 8; j++) {
    newNibble = (newNibble << 1);    // Shift 1 bit to the left
    newNibble = newNibble | port[i].pin[j].result;
  }
  if (newNibble != lowNibble) {
    lowNibble = newNibble;
    sendLowNibble = true;
  }
  // High nibble after
  newNibble = 0;
  for (uint8_t j = 0; j < 4; j++) {
    newNibble = (newNibble << 1);    // Shift 1 bit to the left
    newNibble = newNibble | port[i].pin[j].result;
  }
  if (newNibble != highNibble) {
    highNibble = newNibble;
    sendHighNibble = true;
  }
  // STEP 2: if a change was detected, send the new nibble value
  if (sendLowNibble)  rsbus.send4bits(LowBits,  lowNibble);
  if (sendHighNibble) rsbus.send4bits(HighBits, highNibble);
  //
  // STEP 3: Check if we have to (re)establish a RS-Bus connection.
  // This is the case after a decoder (re)start or after a RS-Bus error. 
  uint8_t startValue = (highNibble << 4 | lowNibble);
  if (rsbus.feedbackRequested) rsbus.send8bits(startValue);
  //
  // STEP 4: Check if the buffer contains feedback data, and the ISR is ready to send that data via the UART.  
  rsbus.checkConnection();
  //
  // STEP 5: Maintain the RS LED
  if (sendLowNibble || sendHighNibble) {
    digitalWriteFast(LED_FB, HIGH);
    RSLedTimer.setTime(1000); 
  } // Step 3: After 1 second turn the LED off
  if (RSLedTimer.expired()) {digitalWriteFast(LED_FB, LOW);}
}


// *******************************************************************************************************
// TODO: MAY BE REMOVED
unsigned long TLast;
uint8_t value;
void CommonRSBusClass::test(uint8_t busNr) {
  unsigned long TNow = millis();
  if ((TNow - TLast) > 500) {
    if (value == 0)  value = 1;
    TLast = TNow;
    feedback[busNr].rsbus.send4bits(LowBits, value);   // Tell the library to buffer these 8 bits for later sending
    value = value * 2;
    if (value > 16)  value = 1;
  }
}
