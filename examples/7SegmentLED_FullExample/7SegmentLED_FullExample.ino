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
  PIN_CLK
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

  String numericalStrings[] = {
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

  for (const auto& s : numericalStrings) {
    Serial.print("display '"); Serial.print(s); Serial.println("'");
    display.displayNumericalString(s);
    delay(1000);
  }

  String hexNumericalStrings[] = {
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

  for (const auto& s : hexNumericalStrings) {
    Serial.print("display '"); Serial.print(s); Serial.println("'");
    display.displayNumericalString(s);
    delay(1000);
  }

  Serial.println("display integer 1~max");

  for (float e = 0.0f; e <= (float)display.numberOfDigits(); e += 0.01f) {
    display.display((int32_t)pow(10.0f, e));
    delay(10);
  }

  Serial.println("display integer -1~min");

  for (float e = 0.0f; e <= (float)(display.numberOfDigits() - 1); e += 0.01f) {
    display.display(-(int32_t)pow(10.0f, e));
    delay(10);
  }

  Serial.println("display hex integer 0x1~max");

  for (float e = 0.0f; e <= (float)display.numberOfDigits(); e += 0.002f) {
    display.displayHex((int32_t)pow(16.0f, e));
    delay(10);
  }

  Serial.println("display float +min~+max");

  for (float e = -(float)display.numberOfDigits(); e <= +(float)display.numberOfDigits(); e += 0.01f) {
    display.display((float)pow(10.0f, e));
    delay(10);
  }

  Serial.println("display float -min~-max");

  for (float e = -(float)(display.numberOfDigits() - 1); e <= +(float)(display.numberOfDigits() - 1); e += 0.01f) {
    display.display(-(float)pow(10.0f, e));
    delay(10);
  }

  Serial.println("display integer with zero padding");

  for (float e = 0.0f; e <= (float)display.numberOfDigits(); e += 0.02f) {
    display.displayZeroPadding((int32_t)pow(10.0f, e));
    delay(10);
  }

  for (float e = 0.0f; e <= (float)(display.numberOfDigits() - 1); e += 0.02f) {
    display.displayZeroPadding(-(int32_t)pow(10.0f, e));
    delay(10);
  }

  for (float e = 0.0f; e <= (float)display.numberOfDigits(); e += 0.01f) {
    display.displayHexZeroPadding((int32_t)pow(16.0f, e));
    delay(10);
  }

  Serial.println("display float with width and precision");

  for (float e = -(float)display.numberOfDigits(); e <= +(float)display.numberOfDigits(); e += 0.02f) {
    display.display((float)pow(10.0f, e), 1, 2); // in format 'x.xx'
    delay(10);
  }

  for (float e = -(float)(display.numberOfDigits() - 1); e <= +(float)(display.numberOfDigits() - 1); e += 0.02f) {
    display.display(-(float)pow(10.0f, e), 1, 2); // in format 'x.xx'
    delay(10);
  }

  Serial.println("display integer 0");
  display.display((int32_t)0);
  delay(1000);

  Serial.println("display float +0");
  display.display(0.0f);
  delay(1000);

  Serial.println("display float -0");
  display.display(-0.0f);
  delay(1000);

  Serial.println("display float +INF");
  display.display((float)+INFINITY);
  delay(1000);

  Serial.println("display float -INF");
  display.display((float)-INFINITY);
  delay(1000);

  Serial.println("display float NaN");
  display.display((float)NAN);
  delay(1000);

  Serial.println("display custom characters");

  for (auto i = 0; i < 5; i++) {
    display.displaySegmentBits({
      0b01110110, // H
      0b01111001, // E
      0b00111000, // L
      0b00111000, // L
      0b01011100, // o
      0b10000110, // 1. (!)
    });
    delay(500);

    display.clear();
    delay(500);
  }

  Serial.println("display decimal point per digit");

  for (auto digit = 0u; digit < display.numberOfDigits(); digit++) {
    display.clear();

    display.setDecimalPointOnAt(digit);

    delay(500);
  }

  Serial.println("display hexadecimal number per digit");

  for (auto digit = 0u; digit < display.numberOfDigits(); digit++) {
    display.clear();

    for (auto number = 0; number < 0x10; number++) {
      display.setHexNumberAt(digit, number);

      delay(100);
    }
  }

  Serial.println("display decimal number per digit");

  for (auto digit = 0u; digit < display.numberOfDigits(); digit++) {
    display.clear();

    for (auto number = 0; number < 10; number++) {
      display.setDecimalNumberAt(digit, number);

      delay(100);
    }
  }

  Serial.println("set each segment on (A~G and DP)");

  for (auto digit = 0u; digit < display.numberOfDigits(); digit++) {
    display.clear();

    for (auto segment = 0u; segment < 8u; segment++) {
      display.setSegmentBitsAt(digit, 0b1 << segment);

      delay(100);
    }
  }

  Serial.println("clear only character segments (A~G)");

  for (auto digit = 0u; digit < display.numberOfDigits(); digit++) {
    display.setSegmentBitsAt(digit, 0b11111111); // set all segments on
  }

  delay(1000);

  display.clearCharacterSegments();

  delay(1000);

  display.clear();

  delay(1000);


  Serial.println("clear only decimal point segment (DP)");

  for (auto digit = 0u; digit < display.numberOfDigits(); digit++) {
    display.setSegmentBitsAt(digit, 0b11111111); // set all segments on
  }

  delay(1000);

  display.clearDecimalPointSegments();

  delay(1000);

  display.clear();

  delay(1000);
}