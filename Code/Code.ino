//*****************************************************************************************************
//
// File:      TMC-24-IO.ino
// Author:    Aiko Pras
// History:   2024/02/29 AP Version 1.0
//
// Purpose:   24 Channel (3 x 8) IO-decoder for the TMC (Twentse Modelspoorwegclub).
//            Interfaces between the 25 pin SUB-D connectors that are used in the current layout,
//            and the DCC signal (for Switches) and (Lenz) RS-Bus (for feedback).
//
// Processor AVR64DA64
// Programmer Serial UPDI
//
// Behaviour at the DCC side is comparible to a normal (switch) decoder. The DCC address can be changed 
// via the onboard button. CVs (Configuration Variables) allow modification of various settings; these
// CVs can be accessed via Service Mode (Pogramming Track) as well as PoM (Pogramming on Main) messages.
// 
// Behaviour at the RS-Bus side is comparible to a normal feedback decoder. The RS-Bus may be any 
// address between 1 and 127; address 128 is reserved for PoM response messages.
// Such PoM response messages can be used together with dedicated PC/MAC software, such as:
// https://github.com/aikopras/Programmer-Decoder-POM
// https://github.com/aikopras/Programmer-GBM-POM
//           
//******************************************************************************************************
#include <Arduino.h>                  // For general definitions
#include <AP_DCC_Decoder_Core.h>      // To include all objects, such as dcc, accCmd, etc.
#include "hardware.h"                 // Pin assignments
#include "myDefaults.h"               // Default values for this specific board
#include "dipSwitches.h"              // To handle the three DIP switches
#include "dccIn.h"                    // To handle all DCC input signals
#include "input.h"                    // To handle all IO input pins
#include "rsBus.h"                    // To sen RS-Bus feedback messages

DccTimer inputIntervalTimer;          // To avoid overload, we check input pins only when timer expires
uint8_t startUpPhase;                 // To assure we have sufficient samples for a stable input value   


//******************************************************************************************************
void print_CVs_and_Other_Info() {
  // Print for testing purposes
  for (uint8_t i = 0; i <= 36; i++) {
    Serial.print("CV"); 
    Serial.print(i); 
    Serial.print(": "); 
    Serial.println(cvValues.read(i)); 
  }
  if (cvValues.addressNotSet()) Serial.println("Address not set");
  Serial.print("First Decoder Address: "); 
  Serial.println(cvValues.storedAddress()); 
  Serial.print("First RS-Bus Address: "); 
  Serial.println(feedback[1].rsbus.address - 1); 
}                  


void init_serial() {
  // Serial monitor is used for debugging
  delay(100);
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println("TMC 24 Channel IO Decoder");
  delay(100);
}


//******************************************************************************************************
void setup() {
  init_serial();
  //
  leds.init();
  //
  // Initialise the 3 DIP switch input pins, as well as the (DIR register of the) 3 ports as IN or OUT 
  dipSwitches.init();
  //
  // Initialise the DCC input
  dcc_in.init();
  //
  // initialse each of the three I/O ports
  for (uint8_t i = 0; i < 3; i++) {port[i].init();}
  //
  // Assign addresses to each of the three RS-Bus connections
  RSCommon.init();
  //
  // To reduce load, we do not sample input pins continously, but only at a certain interval (in ms)
  inputIntervalTimer.setTime(cvValues.read(Int_Samples));
  inputIntervalTimer.start();
  //
  // To prevent us from sending feedback data before the value of the input pins are stable,
  // we introduce an artificial delay to ensure we have collected a sufficient number of samples
  // to expect the input value is stable. We take an "arbitraty value as starting point.
  startUpPhase = cvValues.read(Start_Delay);
  //
  print_CVs_and_Other_Info();
}


//******************************************************************************************************
void loop() { 
  // Step 1: Read the DIP switch settings, and (re)configure DIR of the AVR output ports if needed
  dipSwitches.check();
  // Step2: Check if we received a DCC message for this decoder
  // If yes, write to the associataed output port, if the DIP switches allow that
  dcc_in.check();
  // Step3: Check for each port that is configured as input if one or more input pins changed.
  // To reduce load, we sample only at certain intervals (default: 10 ms)
  if (inputIntervalTimer.expired()) {
    inputIntervalTimer.restart();
    // Decrease the startUpPhase variable, till it becomes zero
    if (startUpPhase > 0) startUpPhase--;
    // Check if we need to change the DIR register of an input port
    if (dipSwitches.dip1setting == MELDEN) {port[0].check(0, POORT0_IN_REGISTER);}
    if (dipSwitches.dip2setting == MELDEN) {port[1].check(1, POORT1_IN_REGISTER);}
    if (dipSwitches.dip3setting == MELDEN) {port[2].check(2, POORT2_IN_REGISTER);}
  }
  // Step 4: As frequent as possible we have to check for each RS-Bus connection if the buffer 
  // contains feedback data, and the ISR is ready to send that data via the UART. 
  // If necessary, we also (re)connect after a decoder (re)start or after a RS-Bus error.
  // To prevent us from sending instable values during startup, we wait till that phase is over.
  if (!startUpPhase) {
    if (dipSwitches.dip1setting == MELDEN) {feedback[0].check(0);}
    if (dipSwitches.dip2setting == MELDEN) {feedback[1].check(1);}
    if (dipSwitches.dip3setting == MELDEN) {feedback[2].check(2);}
  }
  // Step 5: as frequent as possible we should check if the programming button is pushed and if
  // the status of the onboard LED should be changed. We also check the RS-Bus polling routine,
  // which resets the RS-Bus counter after all 128 decoders have been polled.  
  // In addition, we check if PoM feedback messages should be returned via the RS-Bus (address 128).
  decoderHardware.update();
  RSCommon.checkLed();               // do we have a valid RS-Bus signal?
  // Step XXX: For testing purposes: send periodic transmission of RS-Bus messages
//  RSCommon.test(2);  
}   
