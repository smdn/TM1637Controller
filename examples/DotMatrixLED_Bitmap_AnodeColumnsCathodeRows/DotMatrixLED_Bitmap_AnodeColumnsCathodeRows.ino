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

auto display = TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<
  5, // The number of columns
  7  // The number of rows
>(
  PIN_DIO,
  PIN_CLK
);

uint8_t bitmap_smile[display.numberOfRows()] = { // ☺
//→C O L S
  0b00000, // ↓
  0b01010, // R
  0b01010, // O
  0b00000, // W
  0b10001, // S
  0b01110,
  0b00000,
};
uint8_t bitmap_number9[display.numberOfRows()] = { // 9
//→C O L S
  0b01110, // ↓
  0b10001, // R
  0b10001, // O
  0b01110, // W
  0b00001, // S
  0b00001,
  0b01110,
};

uint8_t rotated_bitmap_smile[display.numberOfColumns()] = { // ☺
//→R O W S
  0b0000100, // C
  0b0110010, // O
  0b0000010, // L
  0b0110010, // S
  0b0000100, // ↑
};
uint8_t rotated_bitmap_number9[display.numberOfColumns()] = { // 9
//→R O W S
  0b0110110, // C
  0b1001001, // O
  0b1001001, // L
  0b1001001, // S
  0b0110000, // ↑
};

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
  Serial.println("draw bitmap");

  display.draw(bitmap_smile);
  delay(1000);

  display.draw(bitmap_number9);
  delay(1000);

  Serial.println("draw rotated bitmap");

  display.drawRotated(rotated_bitmap_smile);
  delay(1000);

  display.drawRotated(rotated_bitmap_number9);
  delay(1000);
}
