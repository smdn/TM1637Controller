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

#ifndef TM1637_OSL40391IXController_SegmentAddressing_h
#define TM1637_OSL40391IXController_SegmentAddressing_h

#include "TM1637_7SegmentLEDController.h"

class OSL40391IXStandardSegmentAddressing : public StandardSegmentAddressing {
  public:
    // [OSL40391-IX]
    //                           D3
    //      --     --   D1    --  o  --
    //    /  /   /  /   o   /  /   /  /
    //    --     --        --     --
    //  /  /   /  /   o   /  /   /  /
    //  -- .   -- .  D2   -- .   -- .
    //
    // segment | TM1637 | n-th bit
    //         |(GRID-5)| (LSBFIRST)
    //---------+--------+-----------
    //   D1    |  SEG1  |    0
    //   D2    |  SEG2  |    1
    //   D3    |  SEG3  |    2
    //    -    |  SEG4  |    3
    //    -    |  SEG5  |    4
    //    -    |  SEG6  |    5
    //    -    |  SEG7  |    6
    //    -    |  SEG8  |    7
    static const uint8_t SEGMENTBITS_COLON_UPPER = 0b00000001;
    static const uint8_t SEGMENTBITS_COLON_LOWER = 0b00000010;
    static const uint8_t SEGMENTBITS_COLON       = 0b00000011;
    static const uint8_t SEGMENTBITS_DEGREESIGN  = 0b00000100;

    // D3
    //  o   ...
    //     .   // b
    //    . g //
    //     ===
    // e //  .
    //  //  .
    //   ...   o DP
    static constexpr uint8_t CHARS_PERCENT = 0b11010010; // assumed to be used with D3 (SEGMENTBITS_DEGREESIGN)

    static constexpr uint8_t CHARS_OUT_OF_RANGE = 0b01000000; // '-'
};

#endif // TM1637_OSL40391IXController_SegmentAddressing_h