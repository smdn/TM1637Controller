using System;
using System.Threading;
using Smdn.Devices.TM1637Controller;
using Smdn.Devices.TM1637Controller.SevenSegmentLEDDisplay;

static class Example {
  public static void Main()
  {
    TM1637.SetupWiringPi(WiringPiSetupFunction.GPIO);

    var display = StandardDisplay.Craete(
      pinDIO: TM1637.PhysicalPinToGpio(16 /*GPIO.23*/), // The pin number connected to TM1637's DIO (#17)
      pinCLK: TM1637.PhysicalPinToGpio(18 /*GPIO.24*/), // The pin number connected to TM1637's CLK (#18)
      numberOfDigits: 6
    );

    display.Begin();

    var numericalStrings = new[] {
      "1",
      "1.2",
      "12.3",
      "123.4",
      "1234.5",
      "12345.6",
      "123456.7",
      "-1",
      "-1.2",
      "-12.3",
      "-123.4",
      "-1234.5",
      "-12345.6",
      "     0",
      "    01",
      "   012",
      "  0123",
      " 01234",
      "012345",
      "0 1234",
      "01 234",
      "012 34",
      "0123 4",
      "01234 ",
      "      ",
      "01-01",
      "12-31",
      "-.-.-.-.-.-.",
    };

    foreach (var s in numericalStrings) {
      Console.WriteLine($"display '{s}'");
      display.DisplayNumericalString(s);
      Thread.Sleep(1000);
    }

    var hexNumericalStrings = new[] {
      "B",
      "BA",
      "BAD",
      "BADC",
      "badca",
      "badcaf",
      "badcafe",
      "-A",
      "-B.A",
      "-CB.A",
      "-DCB.A",
      "-EDCB.A",
      "-FEDCB.A",
    };

    foreach (var s in hexNumericalStrings) {
      Console.WriteLine($"display '{s}'");
      display.DisplayNumericalString(s);
      Thread.Sleep(1000);
    }

    Console.WriteLine("display integer 1~max");

    for (var e = 0.0f; e <= (float)display.NumberOfDigits; e += 0.01f) {
      display.Display((int)MathF.Pow(10.0f, e));
      Thread.Sleep(10);
    }

    Console.WriteLine("display integer -1~min");

    for (var e = 0.0f; e <= (float)(display.NumberOfDigits - 1); e += 0.01f) {
      display.Display(-(int)MathF.Pow(10.0f, e));
      Thread.Sleep(10);
    }

    Console.WriteLine("display hex integer 0x1~max");

    for (var e = 0.0f; e <= (float)display.NumberOfDigits; e += 0.002f) {
      display.DisplayHex((int)MathF.Pow(16.0f, e));
      Thread.Sleep(10);
    }

    Console.WriteLine("display float +min~+max");

    for (var e = -(float)display.NumberOfDigits; e <= +(float)display.NumberOfDigits; e += 0.01f) {
      display.Display((float)MathF.Pow(10.0f, e));
      Thread.Sleep(10);
    }

    Console.WriteLine("display float -min~-max");

    for (var e = -(float)(display.NumberOfDigits - 1); e <= +(float)(display.NumberOfDigits - 1); e += 0.01f) {
      display.Display(-(float)MathF.Pow(10.0f, e));
      Thread.Sleep(10);
    }

    Console.WriteLine("display integer with zero padding");

    for (var e = 0.0f; e <= (float)display.NumberOfDigits; e += 0.02f) {
      display.DisplayZeroPadding((int)MathF.Pow(10.0f, e));
      Thread.Sleep(10);
    }

    for (var e = 0.0f; e <= (float)(display.NumberOfDigits - 1); e += 0.02f) {
      display.DisplayZeroPadding(-(int)MathF.Pow(10.0f, e));
      Thread.Sleep(10);
    }

    for (var e = 0.0f; e <= (float)display.NumberOfDigits; e += 0.01f) {
      display.DisplayHexZeroPadding((int)MathF.Pow(16.0f, e));
      Thread.Sleep(10);
    }

    Console.WriteLine("display float with width and precision");

    for (var e = -(float)display.NumberOfDigits; e <= +(float)display.NumberOfDigits; e += 0.02f) {
      display.Display((float)MathF.Pow(10.0f, e), 1, 2); // in format 'x.xx'
      Thread.Sleep(10);
    }

    for (var e = -(float)(display.NumberOfDigits - 1); e <= +(float)(display.NumberOfDigits - 1); e += 0.02f) {
      display.Display(-(float)MathF.Pow(10.0f, e), 1, 2); // in format 'x.xx'
      Thread.Sleep(10);
    }

    Console.WriteLine("display integer 0");
    display.Display(0);
    Thread.Sleep(1000);

    Console.WriteLine("display float +0");
    display.Display(0.0f);
    Thread.Sleep(1000);

    Console.WriteLine("display float -0");
    display.Display(-0.0f);
    Thread.Sleep(1000);

    Console.WriteLine("display float +INF");
    display.Display(float.PositiveInfinity);
    Thread.Sleep(1000);

    Console.WriteLine("display float -INF");
    display.Display(float.NegativeInfinity);
    Thread.Sleep(1000);

    Console.WriteLine("display float NaN");
    display.Display(float.NaN);
    Thread.Sleep(1000);

    Console.WriteLine("display decimal point per digit");

    for (var digit = 0; digit < display.NumberOfDigits; digit++) {
      display.Clear();

      display.SetDecimalPointOnAt(digit);

      Thread.Sleep(500);
    }

    Console.WriteLine("display hexadecimal number per digit");

    for (var digit = 0; digit < display.NumberOfDigits; digit++) {
      display.Clear();

      for (var number = 0; number < 0x10; number++) {
        display.SetHexNumberAt(digit, number);

        Thread.Sleep(100);
      }
    }

    Console.WriteLine("display decimal number per digit");

    for (var digit = 0; digit < display.NumberOfDigits; digit++) {
      display.Clear();

      for (var number = 0; number < 10; number++) {
        display.SetDecimalNumberAt(digit, number);

        Thread.Sleep(100);
      }
    }

    Console.WriteLine("set each segment on (A~G and DP)");

    for (var digit = 0; digit < display.NumberOfDigits; digit++) {
      display.Clear();

      for (var segment = 0; segment < 8; segment++) {
        display.SetSegmentBitsAt(digit, (byte)(0b1 << segment));

        Thread.Sleep(100);
      }
    }

    Console.WriteLine("clear only character segments (A~G)");

    for (var digit = 0; digit < display.NumberOfDigits; digit++) {
      display.SetSegmentBitsAt(digit, (byte)0b11111111); // set all segments on
    }

    Thread.Sleep(1000);

    display.ClearCharacterSegments();

    Thread.Sleep(1000);

    display.Clear();

    Thread.Sleep(1000);


    Console.WriteLine("clear only decimal point segment (DP)");

    for (var digit = 0; digit < display.NumberOfDigits; digit++) {
      display.SetSegmentBitsAt(digit, 0b11111111); // set all segments on
    }

    Thread.Sleep(1000);

    display.ClearDecimalPointSegments();

    Thread.Sleep(1000);

    display.Clear();

    Thread.Sleep(1000);
  }
}
