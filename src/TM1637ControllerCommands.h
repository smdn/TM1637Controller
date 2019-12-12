// 
// Copyright (c) 2019 smdn (https://smdn.jp/)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef TM1637ControllerCommands_h
#define TM1637ControllerCommands_h

#ifdef PLATFORM_RASPBERRY_PI
#include <stdint.h>
#else
#include <Arduino.h>
#endif

// data sheet:
//   http://akizukidenshi.com/download/ds/titanmicro/TM1637_V2.4_EN.PDF

class TM1637ControllerCommands {
  protected:
    // MSB--LSB|
    // --------+----------------------------------------------------
    //         | Data command
    // 01--XXXX| - Data command setting
    // 01----XX|   - Data write and read mode setting
    // 01----00|     - Write data to display register
    // 01----01|     - Read key scan data
    // 01---X--|   - Adress adding mode setting
    // 01---0--|     - Automatic address adding
    // 01---1--|     - Fix address
    // 01--X---|   - Test mode setting (for internal)
    // 01--0---|     - Normal mode
    // 01--1---|     - Test mode
    static constexpr uint8_t DATACOMMANDSETTING_READWRITEMODE_WRITE   = 0b01000000u;
    static constexpr uint8_t DATACOMMANDSETTING_READWRITEMODE_READ    = 0b01000001u;
    static constexpr uint8_t DATACOMMANDSETTING_ADDRESSMODE_AUTOMATIC = 0b01000000u;
    static constexpr uint8_t DATACOMMANDSETTING_ADDRESSMODE_FIXED     = 0b01000100u;

    // MSB--LSB|
    // --------+----------------------------------------------------
    //         | Data command
    // 10--XXXX| - Display control
    // 10---XXX|   - Setting of extinction number :
    // 10---000|     - Pulse width is set as  1/16
    // 10---001|     - Pulse width is set as  2/16
    // 10---010|     - Pulse width is set as  4/16
    // 10---011|     - Pulse width is set as 10/16
    // 10---100|     - Pulse width is set as 11/16
    // 10---101|     - Pulse width is set as 12/16
    // 10---110|     - Pulse width is set as 13/16
    // 10---111|     - Pulse width is set as 14/16
    // 10--X---|   - Display switch setting :
    // 10--0---|     - Display OFF
    // 10--1---|     - Display ON
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_01_16TH = 0b10000000u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_02_16TH = 0b10000001u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_04_16TH = 0b10000010u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_10_16TH = 0b10000011u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_11_16TH = 0b10000100u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_12_16TH = 0b10000101u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_13_16TH = 0b10000110u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_14_16TH = 0b10000111u;
    static constexpr uint8_t DISPLAYCONTROL_DIMMINGRATIO_MASK_   = 0b10000111u;

    static constexpr uint8_t DISPLAYCONTROL_DISPLAYSWITCH_OFF    = 0b10000000u;
    static constexpr uint8_t DISPLAYCONTROL_DISPLAYSWITCH_ON     = 0b10001000u;
    static constexpr uint8_t DISPLAYCONTROL_DISPLAYSWITCH_MASK_  = 0b10001000u;

    // MSB--LSB|
    // --------+----------------------------------------------------
    //         | Data command
    // 11--XXXX| - Address command setting
    //         |   - Display address :
    // 11--0000|     - C0H
    // 11--0001|     - C1H
    // 11--0010|     - C2H
    // 11--0011|     - C3H
    // 11--0100|     - C4H
    // 11--0101|     - C5H
    static constexpr uint8_t ADRESSCOMMANDSETTING_DISPLAYADDRESS_BASE = 0b11000000u;
    static constexpr uint8_t ADRESSCOMMANDSETTING_DISPLAYADDRESS_C0H  = 0b11000000u;
    static constexpr uint8_t ADRESSCOMMANDSETTING_DISPLAYADDRESS_C1H  = 0b11000001u;
    static constexpr uint8_t ADRESSCOMMANDSETTING_DISPLAYADDRESS_C2H  = 0b11000010u;
    static constexpr uint8_t ADRESSCOMMANDSETTING_DISPLAYADDRESS_C3H  = 0b11000011u;
    static constexpr uint8_t ADRESSCOMMANDSETTING_DISPLAYADDRESS_C4H  = 0b11000100u;
    static constexpr uint8_t ADRESSCOMMANDSETTING_DISPLAYADDRESS_C5H  = 0b11000101u;
};

#endif // TM1637ControllerCommands_h