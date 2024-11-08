// *******************************************************************************************************
// File:      dccIn.h
// Author:    Aiko Pras
// History:   2024/04/26 AP Version 1.0
// 
// Purpose:   Handling the incoming accessory (switch commands)
// 
// *******************************************************************************************************
#pragma once

class dcc_in_class {
  public:
    void init();
    void check();
    void checksave();
    void print_details(uint8_t pin);   // For testing purposes
};


// *******************************************************************************************************
// Definition of external objects, which are declared in dccIn.cpp but used by main 
extern dcc_in_class dcc_in;
extern unsigned int firstDecoderAddress;
