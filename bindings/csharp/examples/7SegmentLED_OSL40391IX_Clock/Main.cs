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

    Console.WriteLine("press key below to switch format of time");
    Console.WriteLine("  'h': hh:mm");
    Console.WriteLine("  'm': mm:ss");

    const int formatHoursMinites = 0;
    const int formatMinutesSeconds = 1;
    var format = formatMinutesSeconds;

    for (;;) {
      if (Console.KeyAvailable) {
        var key = Console.ReadKey(true);

        switch (key.KeyChar) {
          case 'H': case 'h': format = formatHoursMinites; Console.WriteLine(" hh:mm"); break;
          case 'M': case 'm': format = formatMinutesSeconds; Console.WriteLine(" mm:ss"); break;
          default: break;
        }
      }

      switch (format) {
        case formatHoursMinites: display.DisplayTimeOfDayHoursMinutes(DateTime.Now.TimeOfDay); break;
        case formatMinutesSeconds: display.DisplayTimeOfDayMinutesSeconds(DateTime.Now.TimeOfDay); break;
        default: break;
      }

      Thread.Sleep(50);
    }
  }
}
