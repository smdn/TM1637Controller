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

namespace Smdn.Devices.TM1637Controller.SevenSegmentLEDDisplay {
  public interface IDisplay : ITM1637 {
    int NumberOfDigits { get; }
    int DisplayableMaximumInteger { get; }
    int DisplayableMinimumInteger { get; }
    float DisplayableMaximumPlusFloat { get; }
    float DisplayableMinimumPlusFloat { get; }
    float DisplayableMaximumMinusFloat { get; }
    float DisplayableMinimumMinusFloat { get; }

    void Clear(bool flush = true);
    void ClearCharacterSegments(bool flush = true);
    void ClearDecimalPointSegments(bool flush = true);
    void Flush();

    void SetSegmentBitsAt(int digit, byte segmentBits, bool flush = true);
    void SwitchSegmentBitsAt(int digit, byte segmentBits, bool trueForOnOtherwiseOff, bool flush = true);

    void SetDecimalNumberAt(int digit, int decimalNumber, bool flush = true);
    void SetHexNumberAt(int digit, int hexadecimalNumber, bool flush = true);
    void SetDecimalPointOnAt(int digit, bool flush = true);
    void SetDecimalPointOffAt(int digit, bool flush = true);
    void SetDecimalPointAt(int digit, bool trueForOnOtherwiseOff, bool flush = true);

    void Display(int value, bool flush = true);
    void DisplayZeroPadding(int value, bool flush = true);
    void DisplayHex(int value, bool flush = true);
    void DisplayHexZeroPadding(int value, bool flush = true);

//  public void display(string format, int value, bool flush)

    void Display(float value, bool flush = true);
    void Display(float value, int width, int precision, bool flush = true);

    void DisplayNumericalString(string str, bool flush = true);
    void DisplayNumericalString(ReadOnlySpan<char> chars, bool flush = true);
    void DisplayNumericalString(ReadOnlySpan<byte> bytes, bool flush = true);
  }
}
