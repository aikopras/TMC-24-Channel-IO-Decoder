// *******************************************************************************************************
// File:      dccIn.cpp
// Author:    Aiko Pras
// History:   2024/04/26 AP Version 1.0
// 
// Purpose:   Handling the accessory (switch commands)
// 
// ******************************************************************************************************
#include <AP_DCC_Decoder_Core.h>      // To include all objects, such as dcc, accCmd, etc.
#include "hardware.h"                 // Pin assignments and #defines
#include "myDefaults.h"               // Default values for this specific board
#include "dipSwitches.h"              // The three switches that determine MELDEN or SCHAKELEN
#include "dccIn.h"

unsigned int firstDecoderAddress;     // Derived from CV1 + CV9 (1..511)

DccTimer DccLedTimer;                 // To switch the LED off that signals there is a valid DCC signal
DccTimer AccLedTimer;                 // To switch the LED off that signals the DCC command is for me


// ******************************************************************************************************
void dcc_in_class::print_details(uint8_t pin) {
  Serial.print("I/O pin: ");
  Serial.print(pin);
  if (accCmd.position == 1) Serial.println(" +");
    else Serial.println(" -");
}


void dcc_in_class::init() {
  // Step 1: Set CV default values (see CvValues.h. for details) 
  // Decoder type (DecType) and software version (version) are set using cvValues.init().
  // After cvValues.init() is called, modified CV default values are taken from myDefaults.h
  // Updated values take effect after setDefaults() is called, either by a long push of the 
  // onboard programming button, or by a CV-POM or CV-SM message to CV8 (VID).
  cvValues.init(TMC24ChannelIODecoder, 20);
  myDefaults.init();
  // Step 2: initialise the dcc and rsbus objects with addresses and other settings
  decoderHardware.init();
  // For 24 IO pins, we need to listen to 6 decoder addresses
  firstDecoderAddress = cvValues.storedAddress();
  accCmd.setMyAddress(firstDecoderAddress, firstDecoderAddress + 5);
  // We will also listen to PoM messages. As address we use an offset plus the RS Address
  uint16_t myPomAddress = cvValues.read(Offset_PoM) * 100 + cvValues.read(myRSAddr);
  locoCmd.setMyAddress(myPomAddress);
}


void dcc_in_class::check() {
  unsigned int IO_pin;                  // IO pin at which this DCC command is aimed (1..24)
  if (dcc.input()) {    
    // Step 1: Is the received DCC message intended for me?
    if (dcc.cmdType == Dcc::MyAccessoryCmd) {
      // To what I/O pin is it directed and is it ON (+) or OFF (-)
      IO_pin = (accCmd.decoderAddress - firstDecoderAddress) * 4 + accCmd.turnout;
      boolean react = false; 
      switch (IO_pin) {        
        // POORT0
        case 1: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_1, HIGH);
              else digitalWriteFast(POORT0_1, LOW);
          }
        break;
        case 2: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_2, HIGH);
              else digitalWriteFast(POORT0_2, LOW);
          }
        break;
        case 3: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_3, HIGH);
              else digitalWriteFast(POORT0_3, LOW);
          }
        break;
        case 4: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_4, HIGH);
              else digitalWriteFast(POORT0_4, LOW);
          }
        break;
        case 5: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_5, HIGH);
              else digitalWriteFast(POORT0_5, LOW);
          }
        break;
        case 6: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_6, HIGH);
              else digitalWriteFast(POORT0_6, LOW);
          }
        break;
        case 7: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_7, HIGH);
              else digitalWriteFast(POORT0_7, LOW);
          }
        break;
        case 8: 
          if (dipSwitches.dip1setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT0_8, HIGH);
              else digitalWriteFast(POORT0_8, LOW);
          }
        break;
        // POORT1
        case 9: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWrite(POORT1_1, HIGH);
              else digitalWrite(POORT1_1, LOW);
          }
        break;
        case 10: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT1_2, HIGH);
              else digitalWriteFast(POORT1_2, LOW);
          }
        break;
        case 11: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT1_3, HIGH);
              else digitalWriteFast(POORT1_3, LOW);
          }
        break;
        case 12: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT1_4, HIGH);
              else digitalWriteFast(POORT1_4, LOW);
          }
        break;
        case 13: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT1_5, HIGH);
              else digitalWriteFast(POORT1_5, LOW);
          }
        break;
        case 14: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT1_6, HIGH);
              else digitalWriteFast(POORT1_6, LOW);
          }
        break;
        case 15: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT1_7, HIGH);
              else digitalWriteFast(POORT1_7, LOW);
          }
        break;
        case 16: 
          if (dipSwitches.dip2setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT1_8, HIGH);
              else digitalWriteFast(POORT1_8, LOW);
          }
        break;
        // POORT2
        case 17: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWrite(POORT2_1, HIGH);
              else digitalWrite(POORT2_1, LOW);
          }
        break;
        case 18: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT2_2, HIGH);
              else digitalWriteFast(POORT2_2, LOW);
          }
        break;
        case 19: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT2_3, HIGH);
              else digitalWriteFast(POORT2_3, LOW);
          }
        break;
        case 20: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT2_4, HIGH);
              else digitalWriteFast(POORT2_4, LOW);
          }
        break;
        case 21: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT2_5, HIGH);
              else digitalWriteFast(POORT2_5, LOW);
          }
        break;
        case 22: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT2_6, HIGH);
              else digitalWriteFast(POORT2_6, LOW);
          }
        break;
        case 23: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
           react = true;
           if (accCmd.position == HIGH) digitalWriteFast(POORT2_7, HIGH);
              else digitalWriteFast(POORT2_7, LOW);
          }
        break;
        case 24: 
          if (dipSwitches.dip3setting == SCHAKELEN) {
            react = true;
            if (accCmd.position == HIGH) digitalWriteFast(POORT2_8, HIGH);
              else digitalWriteFast(POORT2_8, LOW);
          }
        break;
        default:
        break;
      };
      // Turn the ACC LED on, to indicate we have reacted on the accesory message
      if (react) {
        digitalWriteFast(LED_ACC, HIGH);
        AccLedTimer.setTime(1000);
        print_details(IO_pin);
      }
    }
    else { // PoM or SM programming??
      if (dcc.cmdType == Dcc::MyPomCmd) cvProgramming.processMessage(Dcc::MyPomCmd);
      else if (dcc.cmdType == Dcc::SmCmd) cvProgramming.processMessage(Dcc::SmCmd);
    };
    // Step 2: Turn the DCC LED on, to indicate the DCC signal is valid
    digitalWriteFast(LED_DCC, HIGH);
    DccLedTimer.setTime(1000);
  } // Step 3: After 1 second turn the LED off
  if (DccLedTimer.expired()) {digitalWriteFast(LED_DCC, LOW);}
  if (AccLedTimer.expired()) {digitalWriteFast(LED_ACC, LOW);}
}
