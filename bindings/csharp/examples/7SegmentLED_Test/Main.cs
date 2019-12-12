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

    for (;;) {
      display.DisplayNumericalString(" 8. 8. 8.");
    }
  }
}
