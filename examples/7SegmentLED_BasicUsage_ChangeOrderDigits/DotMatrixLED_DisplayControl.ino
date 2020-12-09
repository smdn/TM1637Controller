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

#include <Arduino.h>
#include <TM1637_DotMatrixLEDController.h>

#if ESP32
#define PIN_DIO 16 // The pin number connected to TM1637's DIO (#17)
#define PIN_CLK 17 // The pin number connected to TM1637's CLK (#18)
#else
#define PIN_DIO 6 // The pin number connected to TM1637's DIO (#17)
#define PIN_CLK 7 // The pin number connected to TM1637's CLK (#18)
#endif

//auto display = TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController< // for anode rows, cathode columns dot matrix LED display
auto display = TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController< // for anode columns, cathode rows dot matrix LED display
  5, // The number of columns
  7  // The number of rows
>(
  PIN_DIO,
  PIN_CLK
);

void setup()
{
#if ESP32
  Serial.begin(115200);
  while (!Serial);
#else
  Serial.begin(9600);
#endif

  display.begin();
  display.fill();
}

void loop()
{
  Serial.println("set display switch off");
  display.setDisplaySwitchOff();
  delay(1000);

  Serial.println("set display switch on");
  display.setDisplaySwitchOn();
  delay(1000);

  Serial.println("set display brightness from 0% to 100%");

  for (auto brightness = 0; brightness < 100; brightness += 10) {
    display.setDisplayBrightness(brightness); // 0% = display off
    delay(250);
  }

  Serial.println("set display brightness from 100% to 0%");

  for (auto brightness = 100; 0 <= brightness; brightness -= 10) {
    display.setDisplayBrightness(brightness);
    delay(250);
  }

  Serial.println("set brightness minimum (1/16 duty cycle)");
  display.setDisplayBrightnessMinimum();
  delay(1000);

  Serial.println("set brightness to darker level (4/16 duty cycle)");
  display.setDisplayBrightnessDarker();
  delay(1000);

  Serial.println("set brightness to brighter level (10/16 duty cycle)");
  display.setDisplayBrightnessBrighter();
  delay(1000);

  Serial.println("set brightness maximum (14/16 duty cycle)");
  display.setDisplayBrightnessMaximum();
  delay(1000);
}