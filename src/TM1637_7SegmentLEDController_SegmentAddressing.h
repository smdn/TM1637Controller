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

#ifndef TM1637_7SegmentLEDController_SegmentAddressing_h
#define TM1637_7SegmentLEDController_SegmentAddressing_h

#ifdef PLATFORM_RASPBERRY_PI
#include <stdint.h>
#else
#include <Arduino.h>
#endif

class StandardSegmentAddressing {
  //        a
  //       ---
  //   f /   / b
  //    / g /
  //    ---
  // e /   / c
  //  /   /
  //  ---   o DP
  //   d
  //
  // segment | TM1637 | n-th bit
  //         |        | (LSBFIRST)
  //---------+--------+-----------
  //    a    |  SEG1  |    0
  //    b    |  SEG2  |    1
  //    c    |  SEG3  |    2
  //    d    |  SEG4  |    3
  //    e    |  SEG5  |    4
  //    f    |  SEG6  |    5
  //    g    |  SEG7  |    6
  //   DP    |  SEG8  |    7
  public:
    static constexpr uint8_t SEGMENTBITS_MASK_CHARACTER    = 0b01111111;
    static constexpr uint8_t SEGMENTBITS_MASK_DECIMALPOINT = 0b10000000;

    static const uint8_t CHARS_HEXADECIMALS[];

    static constexpr uint8_t CHARS_SPACE    = 0b00000000;
    static constexpr uint8_t CHARS_MINUS    = 0b01000000;
    static constexpr uint8_t CHARS_I_OF_INF = 0b00110000;
    static constexpr uint8_t CHARS_N_OF_INF = 0b00110111;
    static constexpr uint8_t CHARS_F_OF_INF = 0b01110001;
    static constexpr uint8_t CHARS_N_OF_NAN = CHARS_N_OF_INF;
    static constexpr uint8_t CHARS_A_OF_NAN = 0b01011111;
};

#endif // TM1637_7SegmentLEDController_SegmentAddressing_h
