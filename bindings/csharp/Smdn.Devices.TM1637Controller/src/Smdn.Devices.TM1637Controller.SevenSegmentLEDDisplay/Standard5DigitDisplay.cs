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
  using TController = Bindings.TM1637_5Digit7SegmentLEDController;

#pragma warning disable CS3009
  public class Standard5DigitDisplay : /*[CLSCompliant(false)]*/ StandardDisplay<TController> {
#pragma warning restore CS3009
    public override int NumberOfDigits => (int)TController.numberOfDigits();
    public override int DisplayableMaximumInteger => TController.displayableMaximumInteger();
    public override int DisplayableMinimumInteger => TController.displayableMinimumInteger();
    public override float DisplayableMaximumPlusFloat => TController.displayableMaximumPlusFloat();
    public override float DisplayableMinimumPlusFloat => TController.displayableMinimumPlusFloat();
    public override float DisplayableMaximumMinusFloat => TController.displayableMaximumMinusFloat();
    public override float DisplayableMinimumMinusFloat => TController.displayableMinimumMinusFloat();

    public Standard5DigitDisplay(int pinDIO, int pinCLK)
      : base(new TController(
          ThrowIfPinNumberOutOfRange(pinDIO, nameof(pinDIO)),
          ThrowIfPinNumberOutOfRange(pinCLK, nameof(pinCLK))
      ))
    {
    }
  }
}