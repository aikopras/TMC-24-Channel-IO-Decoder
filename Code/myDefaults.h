//*****************************************************************************************************
//
// File:      mySettings.h
// Author:    Aiko Pras
// History:   2024/04/27 AP Version 1.0
//
// Purpose:   Each IO-decoder gets unique default addresses for DCC and RS-Bus.
//            Although these addresses may be changed using normal procedure (programming button, 
//            PoM messages), after a factory reset (long button push, wrinting to CV8) the new values
//            will be the default addresses.
//
// The 24 board IO board represents the equivalent of 6 DCC Switch decoders and/or 3 Feedback decoders.
// CV1 should therefore have values in increments of 6.
// Possible values for CV1 are therefore 1, 7, 13, 19, 25, 31, 37, 43, 49 and 55 
// Possible values for CV9 are 0, 1, 2 and 3 
//  
// Possible values for CV10 and therefore 1, 4, 7, 10, ... 124
// Make sure you understand the relation between Accessory addresses and CV1/CV9 values
// See the general discussion on https://github.com/aikopras/AP_DCC_library, as well as the addressing
// explanation in https://github.com/aikopras/AP_DCC_library/blob/main/src/sup_acc.cpp for details
//         
//******************************************************************************************************
#pragma once

// Deze decoder gebruikt:
#define MY_CV1     41    // Decoder address, low order bits (1..64)
#define MY_CV9     2    // Decoder address, high order bits (0..3)
#define MY_CV10    83   // RS-Bus address (1..128 / undefined = 0)

// 529: CV1=5  / CV2=2 / CV10=65
// 553: CV1=11 / CV2=2 / CV10=68
// 577: CV1=17 / CV2=2 / CV10=71
// 601: CV1=23 / CV2=2 / CV10=74
// 625: CV1=29 / CV2=2 / CV10=77
// 649: CV1=35 / CV2=2 / CV10=80
// 673: CV1=41 / CV2=2 / CV10=83
// 697: CV1=47 / CV2=2 / CV10=86
// 721: CV1=53 / CV2=2 / CV10=89
// 745: CV1=59 / CV2=2 / CV10=92
// 769: CV1=1  / CV2=3 / CV10=95
// 793: CV1=7  / CV2=3 / CV10=98
// 817: CV1=13 / CV2=3 / CV10=101
// 841: CV1=19 / CV2=3 / CV10=104
// 865: CV1=25 / CV2=3 / CV10=107


class myDefaults_class {
  public:
    void init();
};


// *******************************************************************************************************
// Definition of the LED object, which is declared in hardware.cpp but used elsewhere 
extern myDefaults_class myDefaults;
