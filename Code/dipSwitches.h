// *******************************************************************************************************
// File:      dipSwitches.h
// Author:    Aiko Pras
// History:   2024/04/27 AP Version 1.0
// 
// Purpose:   Read the DIP switches and (re)configure the outputs if needed 
//            These are the 3 red switches, that can either be "schakelen" or "melden"
// 
// *******************************************************************************************************
#pragma once
#include <Arduino.h>


class dipSwitchClass {
  public:
    void init();           // Configure the three DIP switch pins as input with pull-up
    void check();          // Checks if a DIP switch has changed, and store the associate POORT DIR
//    void print();          // For testing. May be removed

    boolean dip1setting;   // We store the setting of the three DIP switches,
    boolean dip2setting;   // to allow detection of state and changes
    boolean dip3setting;
};


/*****************************************************************************************************/
// Definition of external objects, which are declared in dipSwitches.cpp but used by main 
extern dipSwitchClass dipSwitches;
