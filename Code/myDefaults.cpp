// *******************************************************************************************************
// File:      myDefaults.cpp
// Author:    Aiko Pras
// History:   2024/05/05 AP Version 1.0
// 
// Purpose:   To set the CV defaults
//
// ******************************************************************************************************
#include <AP_DCC_Decoder_Core.h>      // To include all objects, such as dcc, accCmd, etc.
#include "myDefaults.h"


void myDefaults_class::init() {
  cvValues.defaults[myAddrL]       = MY_CV1;
  cvValues.defaults[myAddrH]       = MY_CV9;
  cvValues.defaults[myRSAddr]      = MY_CV10; 
  // cvValues.defaults[CmdStation] = OpenDCC;

}
