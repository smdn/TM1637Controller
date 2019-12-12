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

auto display = TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<
  7, // The number of columns
  5  // The number of rows
>(
  PIN_DIO,
  PIN_CLK
);

uint8_t bitmap_smile[display.numberOfRows()] = { // ☺
//→C O L S
  0b0100010, // ↓
  0b0100010, // R
  0b0000000, // O
  0b1000001, // W
  0b0111110, // S
};
uint8_t bitmap_number99[display.numberOfRows()] = { // 99
//→C O L S
  0b1110111, // ↓
  0b1010101, // R
  0b1110111, // O
  0b0010001, // W
  0b1110111, // S
};

uint8_t rotated_bitmap_smile[display.numberOfColumns()] = { // ☺
//→R O W S
  0b00010,
  0b11001,
  0b00001, // C
  0b00001, // O
  0b00001, // L
  0b11001, // S
  0b00010, // ↑
};
uint8_t rotated_bitmap_number99[display.numberOfColumns()] = { // 99
//→R O W S
  0b11111,
  0b10101,
  0b11101, // C
  0b00000, // O
  0b11111, // L
  0b10101, // S
  0b11101, // ↑
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

  display.draw(bitmap_number99);
  delay(1000);

  Serial.println("draw rotated bitmap");

  display.drawRotated(rotated_bitmap_smile);
  delay(1000);

  display.drawRotated(rotated_bitmap_number99);
  delay(1000);
}
