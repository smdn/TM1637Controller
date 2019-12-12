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
  using TController = Bindings.TM1637_OSL40391IXController;

#pragma warning disable CS3009
  public class OSL40391IXDisplay : /*[CLSCompliant(false)]*/ StandardDisplay<Bindings.TM1637_OSL40391IXController> {
#pragma warning restore CS3009

    public override int NumberOfDigits => (int)TController.numberOfDigits();
    public override int DisplayableMaximumInteger => TController.displayableMaximumInteger();
    public override int DisplayableMinimumInteger => TController.displayableMinimumInteger();
    public override float DisplayableMaximumPlusFloat => TController.displayableMaximumPlusFloat();
    public override float DisplayableMinimumPlusFloat => TController.displayableMinimumPlusFloat();
    public override float DisplayableMaximumMinusFloat => TController.displayableMaximumMinusFloat();
    public override float DisplayableMinimumMinusFloat => TController.displayableMinimumMinusFloat();

    public OSL40391IXDisplay(int pinDIO, int pinCLK)
      : base(new TController(
          ThrowIfPinNumberOutOfRange(pinDIO, nameof(pinDIO)),
          ThrowIfPinNumberOutOfRange(pinCLK, nameof(pinCLK))
      ))
    {
    }

    public void SetColonOn(bool flush = true) => Controller.setColonOn(flush);
    public void SetColonOff(bool flush = true) => Controller.setColonOff(flush);
    public void SetColon(bool trueForOnOtherwiseOff, bool flush = true) => Controller.setColon(trueForOnOtherwiseOff, flush);

    public void SetUpperDotOfColonOn(bool flush = true) => Controller.setUpperDotOfColonOn(flush);
    public void SetUpperDotOfColonOff(bool flush = true) => Controller.setUpperDotOfColonOff(flush);
    public void SetUpperDotOfColon(bool trueForOnOtherwiseOff, bool flush = true) => Controller.setUpperDotOfColon(trueForOnOtherwiseOff, flush);

    public void SetLowerDotOfColonOn(bool flush = true) => Controller.setLowerDotOfColonOn(flush);
    public void SetLowerDotOfColonOff(bool flush = true) => Controller.setLowerDotOfColonOff(flush);
    public void SetLowerDotOfColon(bool trueForOnOtherwiseOff, bool flush = true) => Controller.setLowerDotOfColon(trueForOnOtherwiseOff, flush);

    public void SetDegreeSignOn(bool flush = true) => Controller.setDegreeSignOn(flush);
    public void SetDegreeSignOff(bool flush = true) => Controller.setDegreeSignOff(flush);
    public void SetDegreeSign(bool trueForOnOtherwiseOff, bool flush = true) => Controller.setDegreeSign(trueForOnOtherwiseOff, flush);

    public void SetPercent(bool flush = true) => Controller.setPercent(flush);

    public void DisplayTemperatureCelsius(float temperatureCelsius, bool flush = true) => Controller.displayTemperatureCelsius(temperatureCelsius, flush);
    public void DisplayTemperatureFahrenheit(float temperatureFahrenheit, bool flush = true) => Controller.displayTemperatureFahrenheit(temperatureFahrenheit, flush);
    public void DisplayTemperature(float temperature, bool trueForCelsiusOtherwiseFahrenheit, bool flush = true) => Controller.displayTemperature(temperature, trueForCelsiusOtherwiseFahrenheit, flush);

    public void DisplayPercent(float value, bool flush = true) => Controller.displayPercent(value, flush);

    private static uint ThrowIfElapsedMillisecondsOutOfRange(int elapsedMilliseconds)
      => 0 <= elapsedMilliseconds ? (uint)elapsedMilliseconds : throw new ArgumentOutOfRangeException(nameof(elapsedMilliseconds), elapsedMilliseconds, "must be zero or positive number");

    public void DisplayTimeOfDayMinutesSeconds(TimeSpan elapsedTime, bool blinkColon = true, bool flush = true) => DisplayTimeOfDayMinutesSeconds((int)elapsedTime.TotalMilliseconds);
    public void DisplayTimeOfDayMinutesSeconds(int elapsedMilliseconds, bool blinkColon = true, bool flush = true)
      => Controller.displayTimeOfDayMinutesSeconds(
        ThrowIfElapsedMillisecondsOutOfRange(elapsedMilliseconds),
        blinkColon,
        flush
      );

    public void DisplayTimeOfDayHoursMinutes(TimeSpan elapsedTime, bool blinkColon = true, bool flush = true) => DisplayTimeOfDayHoursMinutes((int)elapsedTime.TotalMilliseconds);
    public void DisplayTimeOfDayHoursMinutes(int elapsedMilliseconds, bool blinkColon = true, bool flush = true)
      => Controller.displayTimeOfDayHoursMinutes(
        ThrowIfElapsedMillisecondsOutOfRange(elapsedMilliseconds),
        blinkColon,
        flush
      );

    public void DisplayElapsedTimeMinutesSeconds(TimeSpan elapsedTime, bool blinkColon = true, bool flush = true) => DisplayElapsedTimeMinutesSeconds((int)elapsedTime.TotalMilliseconds);
    public void DisplayElapsedTimeMinutesSeconds(int elapsedMilliseconds, bool blinkColon = true, bool flush = true)
      => Controller.displayElapsedTimeMinutesSeconds(
        ThrowIfElapsedMillisecondsOutOfRange(elapsedMilliseconds),
        blinkColon,
        flush
      );

    public void DisplayElapsedTimeHoursMinutes(TimeSpan elapsedTime, bool blinkColon = true, bool flush = true) => DisplayElapsedTimeHoursMinutes((int)elapsedTime.TotalMilliseconds);
    public void DisplayElapsedTimeHoursMinutes(int elapsedMilliseconds, bool blinkColon = true, bool flush = true)
      => Controller.displayElapsedTimeHoursMinutes(
        ThrowIfElapsedMillisecondsOutOfRange(elapsedMilliseconds),
        blinkColon,
        flush
      );
  }
}