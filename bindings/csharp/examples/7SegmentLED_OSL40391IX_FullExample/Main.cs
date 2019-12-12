using System;
using System.Threading;
using Smdn.Devices.TM1637Controller;
using Smdn.Devices.TM1637Controller.SevenSegmentLEDDisplay;

static class Example {
  public static void Main()
  {
    TM1637.SetupWiringPi(WiringPiSetupFunction.GPIO);

    var display = new OSL40391IXDisplay(
      pinDIO: TM1637.PhysicalPinToGpio(16 /*GPIO.23*/), // The pin number connected to TM1637's DIO (#17)
      pinCLK: TM1637.PhysicalPinToGpio(18 /*GPIO.24*/)  // The pin number connected to TM1637's CLK (#18)
    );

    display.Begin();

    Console.WriteLine("display current time in format 00:00 (mm:ss)");

    for (var n = 0; n < 50; n++) {
      display.DisplayTimeOfDayMinutesSeconds(DateTime.Now.TimeOfDay, true /* blink colon automaticaly */);
      Thread.Sleep(100);
    }

    Console.WriteLine("display 00:00 ~ 120:00 (mm:ss)");

    for (var e = +2.3979f /* 500ms */; e <= +6.8573f /* 7,200,000ms */; e += 0.02f) {
      display.DisplayElapsedTimeMinutesSeconds((int)MathF.Pow(10.0f, e));
      Thread.Sleep(20);
    }

    Console.WriteLine("display 00:00 ~ 120:00 (hh:mm)");

    for (var e = +2.3979f /* 500ms */; e <= +8.6354f /* 432,000,000ms */; e += 0.02f) {
      display.DisplayElapsedTimeHoursMinutes((int)MathF.Pow(10.0f, e));

      Thread.Sleep(20);
    }

    Console.WriteLine("display 0.00% ~ 1000.0%");

    for (var e = -2.0f; e <= +3.0f + 0.25f; e += 0.02f) {
      display.DisplayPercent(MathF.Pow(10.0f, e));

      Thread.Sleep(20);
    }

    Console.WriteLine("display -0.0% ~ -100.0%");

    for (var e = -1.0f; e <= +2.0f + 0.25f; e += 0.02f) {
      display.DisplayPercent(-MathF.Pow(10.0f, e));

      Thread.Sleep(20);
    }

    Console.WriteLine("display 0.00℃ ~ 1000.0℃");

    for (var e = -2.0f; e <= +3.0f + 0.25f; e += 0.02f) {
      display.DisplayTemperatureCelsius(MathF.Pow(10.0f, e));

      Thread.Sleep(20);
    }

    Console.WriteLine("display -0.0℃ ~ -100.0℃");

    for (var e = -1.0f; e <= +2.0f + 0.25f; e += 0.02f) {
      display.DisplayTemperatureCelsius(-MathF.Pow(10.0f, e));

      Thread.Sleep(20);
    }

    Console.WriteLine("display 0.00℉ ~ 1000.0℉");

    for (var e = -2.0f; e <= +3.0f + 0.25f; e += 0.02f) {
      display.DisplayTemperatureFahrenheit(MathF.Pow(10.0f, e));

      Thread.Sleep(20);
    }

    Console.WriteLine("display -0.0℉ ~ -100.0℉");

    for (var e = -1.0f; e <= +2.0f + 0.25f; e += 0.02f) {
      display.DisplayTemperatureFahrenheit(-MathF.Pow(10.0f, e));

      Thread.Sleep(20);
    }

    Console.WriteLine("display +0 ℃");
    display.DisplayTemperatureCelsius(0.0f);
    Thread.Sleep(1000);

    Console.WriteLine("display -0 ℃");
    display.DisplayTemperatureCelsius(-0.0f);
    Thread.Sleep(1000);

    Console.WriteLine("display +INF ℃");
    display.DisplayTemperatureCelsius(float.PositiveInfinity);
    Thread.Sleep(1000);

    Console.WriteLine("display -INF ℃");
    display.DisplayTemperatureCelsius(float.NegativeInfinity);
    Thread.Sleep(1000);

    Console.WriteLine("display NaN ℃");
    display.DisplayTemperatureCelsius(float.NaN);
    Thread.Sleep(1000);

    Console.WriteLine("display +0 %");
    display.DisplayPercent(0.0f);
    Thread.Sleep(1000);

    Console.WriteLine("display -0 %");
    display.DisplayPercent(-0.0f);
    Thread.Sleep(1000);

    Console.WriteLine("display +INF %");
    display.DisplayPercent(float.PositiveInfinity);
    Thread.Sleep(1000);

    Console.WriteLine("display -INF %");
    display.DisplayPercent(float.NegativeInfinity);
    Thread.Sleep(1000);

    Console.WriteLine("display NaN %");
    display.DisplayPercent(float.NaN);
    Thread.Sleep(1000);

    display.Clear();

    Console.WriteLine("set colon on/off");

    for (var i = 0; i < 6; i++) {
      if (i == 0)
        display.SetColonOn();
      else
        display.SetColonOff();

      Thread.Sleep(300);
    }

    Console.WriteLine("set upper dot of colon on/off");

    for (var i = 0; i < 6; i++) {
      if (i == 0)
        display.SetUpperDotOfColonOn();
      else
        display.SetUpperDotOfColonOff();

      Thread.Sleep(300);
    }

    Console.WriteLine("set lower dot of colon on/off");

    for (var i = 0; i < 6; i++) {
      if (i == 0)
        display.SetLowerDotOfColonOn();
      else
        display.SetLowerDotOfColonOff();

      Thread.Sleep(300);
    }

    Console.WriteLine("set degree sign on/off");

    for (var i = 0; i < 6; i++) {
      if (i == 0)
        display.SetDegreeSignOn();
      else
        display.SetDegreeSignOff();

      Thread.Sleep(300);
    }
  }
}
