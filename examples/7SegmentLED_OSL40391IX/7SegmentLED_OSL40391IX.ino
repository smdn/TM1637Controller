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
#include <TM1637_OSL40391IXController.h>

#if ESP32
#define PIN_DIO 16 // The pin number connected to TM1637's DIO (#17)
#define PIN_CLK 17 // The pin number connected to TM1637's CLK (#18)
#else
#define PIN_DIO 6 // The pin number connected to TM1637's DIO (#17)
#define PIN_CLK 7 // The pin number connected to TM1637's CLK (#18)
#endif

auto display = TM1637_OSL40391IXController(
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
}

void loop()
{
  display.clear();

  Serial.println("display millis() in format 00:00 (mm:ss)");

  for (auto n = 0; n < 50; n++) {
    display.displayTimeOfDayMinutesSeconds(millis(), true /* blink colon automaticaly */);
    delay(100);
  }

  Serial.println("display 00:00 ~ 120:00 (mm:ss)");

  for (auto e = +2.3979f /* 500ms */; e <= +6.8573f /* 7,200,000ms */; e += 0.02f) {
    display.displayElapsedTimeMinutesSeconds((unsigned long)pow(10.0f, e));
    delay(20);
  }

  Serial.println("display 00:00 ~ 120:00 (hh:mm)");

  for (auto e = +2.3979f /* 500ms */; e <= +8.6354f /* 432,000,000ms */; e += 0.02f) {
    display.displayElapsedTimeHoursMinutes((unsigned long)pow(10.0f, e));

    delay(20);
  }

  Serial.println("display 0.00% ~ 1000.0%");

  for (auto e = -2.0f; e <= +3.0f + 0.25f; e += 0.02f) {
    display.displayPercent((float)pow(10.0f, e));

    delay(20);
  }

  Serial.println("display -0.0% ~ -100.0%");

  for (auto e = -1.0f; e <= +2.0f + 0.25f; e += 0.02f) {
    display.displayPercent(-(float)pow(10.0f, e));

    delay(20);
  }

  Serial.println("display 0.00℃ ~ 1000.0℃");

  for (auto e = -2.0f; e <= +3.0f + 0.25f; e += 0.02f) {
    display.displayTemperatureCelsius((float)pow(10.0f, e));

    delay(20);
  }

  Serial.println("display -0.0℃ ~ -100.0℃");

  for (auto e = -1.0f; e <= +2.0f + 0.25f; e += 0.02f) {
    display.displayTemperatureCelsius(-(float)pow(10.0f, e));

    delay(20);
  }

  Serial.println("display 0.00℉ ~ 1000.0℉");

  for (auto e = -2.0f; e <= +3.0f + 0.25f; e += 0.02f) {
    display.displayTemperatureFahrenheit((float)pow(10.0f, e));

    delay(20);
  }

  Serial.println("display -0.0℉ ~ -100.0℉");

  for (auto e = -1.0f; e <= +2.0f + 0.25f; e += 0.02f) {
    display.displayTemperatureFahrenheit(-(float)pow(10.0f, e));

    delay(20);
  }

  Serial.println("display +0 ℃");
  display.displayTemperatureCelsius(0.0f);
  delay(1000);

  Serial.println("display -0 ℃");
  display.displayTemperatureCelsius(-0.0f);
  delay(1000);

  Serial.println("display +INF ℃");
  display.displayTemperatureCelsius((float)+INFINITY);
  delay(1000);

  Serial.println("display -INF ℃");
  display.displayTemperatureCelsius((float)-INFINITY);
  delay(1000);

  Serial.println("display NaN ℃");
  display.displayTemperatureCelsius((float)NAN);
  delay(1000);

  Serial.println("display +0 %");
  display.displayPercent(0.0f);
  delay(1000);

  Serial.println("display -0 %");
  display.displayPercent(-0.0f);
  delay(1000);

  Serial.println("display +INF %");
  display.displayPercent((float)+INFINITY);
  delay(1000);

  Serial.println("display -INF %");
  display.displayPercent((float)-INFINITY);
  delay(1000);

  Serial.println("display NaN %");
  display.displayPercent((float)NAN);
  delay(1000);

  display.clear();

  Serial.println("set colon on/off");

  for (auto i = 0; i < 6; i++) {
    i % 2 == 0
      ? display.setColonOn()
      : display.setColonOff();

    delay(300);
  }

  Serial.println("set upper dot of colon on/off");

  for (auto i = 0; i < 6; i++) {
    i % 2 == 0
      ? display.setUpperDotOfColonOn()
      : display.setUpperDotOfColonOff();

    delay(300);
  }

  Serial.println("set lower dot of colon on/off");

  for (auto i = 0; i < 6; i++) {
    i % 2 == 0
      ? display.setLowerDotOfColonOn()
      : display.setLowerDotOfColonOff();

    delay(300);
  }

  Serial.println("set degree sign on/off");

  for (auto i = 0; i < 6; i++) {
    i % 2 == 0
      ? display.setDegreeSignOn()
      : display.setDegreeSignOff();

    delay(300);
  }
}