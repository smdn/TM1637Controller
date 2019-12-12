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

using System;

namespace Smdn.Devices.TM1637Controller.Bindings {
  partial class TM1637_1Digit7SegmentLEDController : ITM1637_7SegmentLEDController {}
  partial class TM1637_2Digit7SegmentLEDController : ITM1637_7SegmentLEDController {}
  partial class TM1637_3Digit7SegmentLEDController : ITM1637_7SegmentLEDController {}
  partial class TM1637_4Digit7SegmentLEDController : ITM1637_7SegmentLEDController {}
  partial class TM1637_5Digit7SegmentLEDController : ITM1637_7SegmentLEDController {}
  partial class TM1637_6Digit7SegmentLEDController : ITM1637_7SegmentLEDController {}
  partial class TM1637_4Digit5Grid7SegmentLEDControllerBase : ITM1637_7SegmentLEDController {}

  [CLSCompliant(false)]
  public interface ITM1637_7SegmentLEDController {
    void clear(bool flush);
    void clearCharacterSegments(bool flush);
    void clearDecimalPointSegments(bool flush);
    void flush();
    void setSegmentBitsAt(uint digit, byte segmentBits, bool flush);
    void switchSegmentBitsAt(uint digit, byte segmentBits, bool trueForOnOtherwiseOff, bool flush);
    void setDecimalNumberAt(uint digit, byte decimalNumber, bool flush);
    void setHexNumberAt(uint digit, byte hexadecimalNumber, bool flush);
    void setDecimalPointOnAt(uint digit, bool flush);
    void setDecimalPointOffAt(uint digit, bool flush);
    void setDecimalPointAt(uint digit, bool trueForOnOtherwiseOff, bool flush);
    void display(int value, bool flush);
    void displayZeroPadding(int value, bool flush);
    void displayHex(int value, bool flush);
    void displayHexZeroPadding(int value, bool flush);
    void display(float value, bool flush);
    void display(float value, int width, uint precision, bool flush);
    void displayNumericalString(IntPtr str, uint length, bool flush);
  }
}
