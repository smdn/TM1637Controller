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

namespace Smdn.Devices.TM1637Controller {
  public enum WiringPiSetupFunction {
    Default,
    GPIO,
    /// <remarks>requires root privileges</remarks>
    Physical,
    /// <remarks>requires root privileges</remarks>
    Sys,
  }

  public static class TM1637 {
    public static void SetupWiringPi(WiringPiSetupFunction function)
    {
      switch (function) {
        case WiringPiSetupFunction.Default: ThrowIfError(Bindings.TM1637ControllerBindings.wiringPiSetup()); break;
        case WiringPiSetupFunction.GPIO: ThrowIfError(Bindings.TM1637ControllerBindings.wiringPiSetupGpio()); break;
        case WiringPiSetupFunction.Physical: ThrowIfError(Bindings.TM1637ControllerBindings.wiringPiSetupPhys()); break;
        case WiringPiSetupFunction.Sys: ThrowIfError(Bindings.TM1637ControllerBindings.wiringPiSetupSys()); break;
        default:
          throw new ArgumentException($"undefined enum value: {function}", nameof(function));
      }
    }

    public static int PhysicalPinToGpio(int physicalPin) => Bindings.TM1637ControllerBindings.physPinToGpio(physicalPin);
    public static int WiringPiPinToGpio(int wiringPiPin) => Bindings.TM1637ControllerBindings.wpiPinToGpio(wiringPiPin);

    private static void ThrowIfError(int ret)
    {
      // http://wiringpi.com/reference/setup/
      //  "wiringPi version 1 returned an error code if these functions failed for whatever reason. Version 2 returns always returns zero."
      //  "If you want to restore the v1 behaviour, then you need to set the environment variable: WIRINGPI_CODES (to any value, it just needs to exist)"
      if (ret != 0)
        throw new ApplicationException($"setting wiringPi up failed: (error code {ret})");
    }
  }

  public abstract class TM1637<TController>
    : ITM1637
    where TController : Bindings.TM1637Controller
  {
    private readonly TController controller;

    protected TController Controller { get => controller; }

    public const int BrightnessMax = 100;
    public const int BrightnessMin = 0;

    protected static byte ThrowIfPinNumberOutOfRange(int pinNumber, string paramName)
    {
      if (0 <= pinNumber)
        return (byte)pinNumber;

      throw new ArgumentOutOfRangeException(nameof(pinNumber), pinNumber, $"{pinNumber} must be zero or positive number");
    }

    private static uint ThrowIfDisplayBrightnessOutOfRange(int value, string paramName)
    {
      if (BrightnessMin <= value && value <= BrightnessMax)
        return (uint)value;

      throw new ArgumentOutOfRangeException(paramName, value, $"{paramName} must be in range of {BrightnessMin}~{BrightnessMax}");
    }

    protected TM1637(TController controller)
    {
      this.controller = controller ?? throw new ArgumentNullException(nameof(controller));
    }

    public bool DisplaySwitch {
      get => controller.getDisplaySwitch();
      set => controller.setDisplaySwitch(value);
    }

    public int DisplayBrightness {
      get => (int)controller.getDisplayBrightness();
      set => controller.setDisplayBrightness(ThrowIfDisplayBrightnessOutOfRange(value, nameof(DisplayBrightness)));
    }

    public void Begin(int displayBrightnessPercent = BrightnessMax) => controller.begin(ThrowIfDisplayBrightnessOutOfRange(displayBrightnessPercent, nameof(displayBrightnessPercent)));
    public void Reset() => controller.reset();

    public void SetDisplayBrightnessMaximum()  => controller.setDisplayBrightnessMaximum();
    public void SetDisplayBrightnessBrighter() => controller.setDisplayBrightnessBrighter();
    public void SetDisplayBrightnessDarker()   => controller.setDisplayBrightnessDarker();
    public void SetDisplayBrightnessMinimum()  => controller.setDisplayBrightnessMinimum();
  }
}
