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
#include <TM1637_7SegmentLEDController.h>

#if ESP32
#define PIN_DIO 16 // The pin number connected to TM1637's DIO (#17)
#define PIN_CLK 17 // The pin number connected to TM1637's CLK (#18)
#else
#define PIN_DIO 6 // The pin number connected to TM1637's DIO (#17)
#define PIN_CLK 7 // The pin number connected to TM1637's CLK (#18)
#endif

auto display = TM1637_7SegmentLEDController<6 /* The number of digits of 7 segment display */>(
  PIN_DIO,
  PIN_CLK,
  {2, 1, 0, 5, 4, 3} // change order of digits, default is  {0, 1, 2, 3, 4, 5}
);

// equivalent to the expression above
/*
auto display = TM1637_6Digit7SegmentLEDController(
  PIN_DIO,
  PIN_CLK
);
*/

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

  Serial.println("display integer");

  display.display((int32_t)1); delay(500);
  display.display((int32_t)12); delay(500);
  display.display((int32_t)123); delay(500);
  display.display((int32_t)-1); delay(500);
  display.display((int32_t)-12); delay(500);
  display.display((int32_t)-123); delay(500);

  Serial.println("display hex integer");

  display.displayHex((int32_t)0xA); delay(500);
  display.displayHex((int32_t)0xAB); delay(500);
  display.displayHex((int32_t)0xABC); delay(500);

  Serial.println("display floating point");

  display.display(3.14f); delay(500);
  display.display(3.141f); delay(500);
  display.display(3.1415f); delay(500);

  Serial.println("display string-expressed numerical values");

  display.displayNumericalString("123"); delay(1000);
  display.displayNumericalString("-123"); delay(1000);

  display.displayNumericalString("1.23"); delay(1000);
  display.displayNumericalString("-1.23"); delay(1000);

  display.displayNumericalString("12-31"); delay(1000);

  display.displayNumericalString("CAFE"); delay(1000);
  display.displayNumericalString("-C.A.F.E.-"); delay(1000);
}
