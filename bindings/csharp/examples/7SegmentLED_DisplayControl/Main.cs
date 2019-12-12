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

    for (var digit = 0; digit < display.NumberOfDigits; digit++) {
      display.SetSegmentBitsAt(digit, 0b11111111); // set all segments on
    }

    Console.WriteLine("set display switch off");
    display.DisplaySwitch = false;
    Thread.Sleep(1000);

    Console.WriteLine("set display switch on");
    display.DisplaySwitch = true;
    Thread.Sleep(1000);

    Console.WriteLine("set display brightness from 0% to 100%");

    for (var brightness = 0; brightness < 100; brightness += 10) {
      display.DisplayBrightness = brightness; // 0% = display off
      Thread.Sleep(250);
    }

    Console.WriteLine("set display brightness from 100% to 0%");

    for (var brightness = 100; 0 <= brightness; brightness -= 10) {
      display.DisplayBrightness = brightness;
      Thread.Sleep(250);
    }

    Console.WriteLine("set brightness minimum (1/16 duty cycle)");
    display.SetDisplayBrightnessMinimum();
    Thread.Sleep(1000);

    Console.WriteLine("set brightness to darker level (4/16 duty cycle)");
    display.SetDisplayBrightnessDarker();
    Thread.Sleep(1000);

    Console.WriteLine("set brightness to brighter level (10/16 duty cycle)");
    display.SetDisplayBrightnessBrighter();
    Thread.Sleep(1000);

    Console.WriteLine("set brightness maximum (14/16 duty cycle)");
    display.SetDisplayBrightnessMaximum();
    Thread.Sleep(1000);
  }
}
