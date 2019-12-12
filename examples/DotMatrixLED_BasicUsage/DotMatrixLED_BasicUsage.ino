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
}

void loop()
{
  Serial.println("fill/clear entire display");

  for (auto n = 0; n < 6; n++) {
    if (n % 2 == 0)
      display.fill(); // set all pixel on
    else
      display.clear(); // set all pixel off

    delay(250);
  }

  Serial.println("fill/invert entire display");

  for (auto n = 0; n < 6; n++) {
    if (n % 2 == 0)
      display.fill(); // set all pixel on
    else
      display.invert(); // invert all pixel state

    delay(250);
  }

  display.clear();

  Serial.println("set each pixel on");

  for (auto row = 0u; row < display.numberOfRows(); row++) {
    for (auto col = 0u; col < display.numberOfColumns(); col++) {
      display.setOn(col, row);
      delay(50);
    }
  }

  Serial.println("set each pixel off");

  for (auto row = 0u; row < display.numberOfRows(); row++) {
    for (auto col = 0u; col < display.numberOfColumns(); col++) {
      display.setOff(col, row);
      delay(50);
    }
  }

  Serial.println("set each column on");

  for (auto col = 0u; col < display.numberOfColumns(); col++) {
    display.fillColumn(col);
    delay(200);
  }

  Serial.println("set each column off");

  for (auto col = 0u; col < display.numberOfColumns(); col++) {
    display.clearColumn(col);
    delay(200);
  }

  Serial.println("set each row on");

  for (auto row = 0u; row < display.numberOfRows(); row++) {
    display.fillRow(row);
    delay(200);
  }

  Serial.println("set each row off");

  for (auto row = 0u; row < display.numberOfRows(); row++) {
    display.clearRow(row);
    delay(200);
  }

  Serial.println("set top left corner on");

  display.clear();
  display.setOn(0, 0);
  delay(1000);

  Serial.println("set top right corner on");

  display.clear();
  display.setOn(display.numberOfColumns() - 1, 0);
  delay(1000);

  Serial.println("set bottom right corner on");

  display.clear();
  display.setOn(display.numberOfColumns() - 1, display.numberOfRows() - 1);
  delay(1000);

  Serial.println("set bottom left corner on");

  display.clear();
  display.setOn(0, display.numberOfRows() - 1);
  delay(1000);
}
