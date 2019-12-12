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
using System.Runtime.CompilerServices;
using System.Text;

namespace Smdn.Devices.TM1637Controller.SevenSegmentLEDDisplay {
#pragma warning disable CS3024
  public static class StandardDisplay {
    public static IDisplay Craete(int numberOfDigits, int pinDIO, int pinCLK)
    {
      switch (numberOfDigits) {
        case 1: return new Standard1DigitDisplay(pinDIO, pinCLK);
        case 2: return new Standard2DigitDisplay(pinDIO, pinCLK);
        case 3: return new Standard3DigitDisplay(pinDIO, pinCLK);
        case 4: return new Standard4DigitDisplay(pinDIO, pinCLK);
        case 5: return new Standard5DigitDisplay(pinDIO, pinCLK);
        case 6: return new Standard6DigitDisplay(pinDIO, pinCLK);
        default: throw new ArgumentOutOfRangeException(nameof(numberOfDigits), numberOfDigits, $"{nameof(numberOfDigits)} must be in range of 1~6");
      }
    }
  }

  public abstract class StandardDisplay<T7SegmentLEDController>
    : TM1637<T7SegmentLEDController>, IDisplay
    where T7SegmentLEDController : /*[CLSCompliant(false)]*/ Bindings.TM1637Controller, Bindings.ITM1637_7SegmentLEDController
#pragma warning restore CS3024
  {

    public abstract int NumberOfDigits { get; }

    public abstract int DisplayableMaximumInteger { get; }
    public abstract int DisplayableMinimumInteger { get; }
    public abstract float DisplayableMaximumPlusFloat { get; }
    public abstract float DisplayableMinimumPlusFloat { get; }
    public abstract float DisplayableMaximumMinusFloat { get; }
    public abstract float DisplayableMinimumMinusFloat { get; }

    private protected uint ThrowIfDigitOutOfRange(int digit)
    {
      if (0 <= digit && digit < NumberOfDigits)
        return (uint)digit;

      throw new ArgumentOutOfRangeException(nameof(digit), digit, $"{nameof(digit)} must be in range of 0~{NumberOfDigits}");
    }

    protected StandardDisplay(T7SegmentLEDController controller)
      : base(controller)
    {
    }

    public void Clear(bool flush = true) => Controller.clear(flush);
    public void ClearCharacterSegments(bool flush = true) => Controller.clearCharacterSegments(flush);
    public void ClearDecimalPointSegments(bool flush = true) => Controller.clearDecimalPointSegments(flush);
    public void Flush() => Controller.flush();

    public void SetSegmentBitsAt(int digit, byte segmentBits, bool flush = true) => Controller.setSegmentBitsAt(ThrowIfDigitOutOfRange(digit), segmentBits, flush);
    public void SwitchSegmentBitsAt(int digit, byte segmentBits, bool trueForOnOtherwiseOff, bool flush = true) => Controller.switchSegmentBitsAt(ThrowIfDigitOutOfRange(digit), segmentBits, trueForOnOtherwiseOff, flush);

    public void SetDecimalNumberAt(int digit, int decimalNumber, bool flush = true) => Controller.setDecimalNumberAt(ThrowIfDigitOutOfRange(digit), unchecked((byte)decimalNumber), flush);
    public void SetHexNumberAt(int digit, int hexadecimalNumber, bool flush = true) => Controller.setHexNumberAt(ThrowIfDigitOutOfRange(digit), unchecked((byte)hexadecimalNumber), flush);
    public void SetDecimalPointOnAt(int digit, bool flush = true) => Controller.setDecimalPointOnAt(ThrowIfDigitOutOfRange(digit), flush);
    public void SetDecimalPointOffAt(int digit, bool flush = true) => Controller.setDecimalPointOffAt(ThrowIfDigitOutOfRange(digit), flush);
    public void SetDecimalPointAt(int digit, bool trueForOnOtherwiseOff, bool flush = true) => Controller.setDecimalPointAt(ThrowIfDigitOutOfRange(digit), trueForOnOtherwiseOff, flush);

    public void Display(int value, bool flush = true) => Controller.display(value, flush);
    public void DisplayZeroPadding(int value, bool flush = true) => Controller.displayZeroPadding(value, flush);
    public void DisplayHex(int value, bool flush = true) => Controller.displayHex(value, flush);
    public void DisplayHexZeroPadding(int value, bool flush = true) => Controller.displayHexZeroPadding(value, flush);

    public void Display(float value, bool flush = true) => Controller.display(value, flush);
    public void Display(float value, int width, int precision, bool flush = true)
      => Controller.display(
        value,
        width,
        0 <= precision ? (uint)precision : throw new ArgumentOutOfRangeException(nameof(precision), precision, $"{nameof(precision)} must be zero or positive number"),
        flush
      );

    public void DisplayNumericalString(string str, bool flush = true) => DisplayNumericalString((ReadOnlySpan<char>)str, flush);

    public void DisplayNumericalString(ReadOnlySpan<char> chars, bool flush = true)
    {
      Span<byte> bytes = chars.Length < 0x40 ? stackalloc byte[chars.Length] : new byte[chars.Length];

      Encoding.ASCII.GetBytes(chars, bytes);

      DisplayNumericalString(bytes, flush);
    }

    public unsafe void DisplayNumericalString(ReadOnlySpan<byte> bytes, bool flush = true)
    {
      fixed (byte* ptr = bytes) {
        Controller.displayNumericalString(
          (IntPtr)ptr,
          (uint)bytes.Length,
          flush
        );
      }
    }
  }
}
