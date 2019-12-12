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

#include "TM1637Controller.h"

#if PLATFORM_RASPBERRY_PI
using std::min;
#endif

const uint16_t TM1637Controller::BRIGHTNESS_THRESHOLD[] = {
  (uint8_t)(1400u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_14_16TH,
  (uint8_t)(1300u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_13_16TH,
  (uint8_t)(1200u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_12_16TH,
  (uint8_t)(1100u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_11_16TH,
  (uint8_t)(1000u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_10_16TH,
  (uint8_t)( 400u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_04_16TH,
  (uint8_t)( 200u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_02_16TH,
  (uint8_t)( 100u/16) << 8 | DISPLAYCONTROL_DIMMINGRATIO_01_16TH,
};

unsigned int TM1637Controller::pulseWaitIntervalMicroseconds = 5;

uint8_t TM1637Controller::convertBrightness(const unsigned int brightnessPercent)
{
  if (brightnessPercent == 0)
    return DISPLAYCONTROL_DISPLAYSWITCH_OFF;

  auto displayControl = DISPLAYCONTROL_DISPLAYSWITCH_ON;

  for (auto threshold : BRIGHTNESS_THRESHOLD) {
    auto brightness = (threshold & 0xff00u) >> 8;
    auto ratio = threshold & 0x00ffu;

    if (brightness <= brightnessPercent)
      return displayControl | ratio;
  }

  return 0; // will never happen
}

void TM1637Controller::pulseAndWait(const uint8_t pin, const uint8_t value)
{
#if ESP32
  // set pinMode to INPUT and enable pull-up(HIGH), instead of setting HIGH by digitalWrite
  // ref: https://github.com/avishorp/TM1637/
  pinMode(pin, value == HIGH ? INPUT : OUTPUT);
#else
  digitalWrite(pin, value);
#endif

  delayMicroseconds(pulseWaitIntervalMicroseconds);
}

void TM1637Controller::commandStart() const
{
  pulseAndWait(m_pinDIO, LOW);
}

void TM1637Controller::commandStop() const
{
  pulseAndWait(m_pinDIO, LOW);
  pulseAndWait(m_pinCLK, HIGH);
  pulseAndWait(m_pinDIO, HIGH);
}

void TM1637Controller::command(const uint8_t command) const
{
  commandStart();
  commandTransfer(command, LSBFIRST);
  commandStop();
}

void TM1637Controller::commandTransfer(
  const uint8_t commandOrData,
  const uint8_t bitOrder
) const
{
  auto d = commandOrData;

  if (LSBFIRST != bitOrder) {
    // flip bit order
    d = ((d >> 1) & 0x55)| ((d << 1) & 0xaa);
    d = ((d >> 2) & 0x33)| ((d << 2) & 0xcc);
    d =  (d >> 4)         | (d << 4) ;
  }

  for (auto n = 0u; n < NUM_BITS_PER_GRID; n++) {
    pulseAndWait(m_pinCLK, LOW); // n-th CLK falling

    pulseAndWait(m_pinDIO, (d & 0b00000001) ? HIGH : LOW); // n-th bit of command or data

    d >>= 1;

    pulseAndWait(m_pinCLK, HIGH); // n-th CLK rising
  }

  pulseAndWait(m_pinCLK, LOW); // 9th CLK falling

  // wait for ACK
  pulseAndWait(m_pinDIO, HIGH);
  pinMode(m_pinDIO, INPUT);

  pulseAndWait(m_pinCLK, HIGH); // 9th clock CLK rising

  if (LOW != digitalRead(m_pinDIO)) {
    //Serial.println("expected ACK signal not answered");
    // XXX: should return error code?
  }

  // revert pin state
  pinMode(m_pinDIO, OUTPUT);

  pulseAndWait(m_pinCLK, LOW);
}

void TM1637Controller::begin(const unsigned int displayBrightnessPercent)
{
  setDisplayBrightness(displayBrightnessPercent);

  reset();

  // clear register
  uint8_t data[NUM_OF_GRIDS] = {0};

  transferDataToAddressAutomatic(data, NUM_OF_GRIDS, LSBFIRST, 0);
}

void TM1637Controller::reset() const
{
  // initialize pin state
  pinMode(m_pinDIO, OUTPUT);
  pinMode(m_pinCLK, OUTPUT);

  commandStop();

  // initialize display state
  command(m_displayControl);
}

unsigned int TM1637Controller::getDisplayBrightness() const
{
  if (!getDisplaySwitch())
    return 0; // off

  uint8_t dimmingRatio = m_displayControl & DISPLAYCONTROL_DIMMINGRATIO_MASK_;

  for (auto threshold : BRIGHTNESS_THRESHOLD) {
    auto brightness = (threshold & 0xff00u) >> 8;
    uint8_t ratio = threshold & 0x00ffu;

    if (ratio == dimmingRatio)
      return brightness;
  }

  return 0; // will never happen
}

void TM1637Controller::setDisplayControl(
  const uint8_t newDisplayControl
)
{
  if (m_displayControl == newDisplayControl)
    return; // do nothing

  m_displayControl = newDisplayControl;

  command(m_displayControl);
}

void TM1637Controller::transferDataToAddressFixed(
  const uint8_t data,
  const uint8_t bitOrder,
  const unsigned int displayAddress
) const
{
  if (NUM_OF_DISPLAYADDRESSES <= displayAddress)
    return; // display address out of range

#if PLATFORM_RASPBERRY_PI
  // XXX: initialize state before transfer
  reset();
#endif

  // transfer data command setting
  command(DATACOMMANDSETTING_READWRITEMODE_WRITE |
          DATACOMMANDSETTING_ADDRESSMODE_FIXED);

  // transfer display data
  commandStart();

  commandTransfer((uint8_t)(ADRESSCOMMANDSETTING_DISPLAYADDRESS_BASE + displayAddress));

  commandTransfer(data, bitOrder);

  commandStop();
}

void TM1637Controller::transferDataToAddressAutomatic(
  const uint8_t* const dataSequence,
  const size_t numberOfData,
  const uint8_t bitOrder,
  const unsigned int firstDisplayAddress
) const
{
  if (NUM_OF_DISPLAYADDRESSES <= firstDisplayAddress)
    return; // display address out of range

#if PLATFORM_RASPBERRY_PI
  // XXX: initialize state before transfer
  reset();
#endif

  // transfer data command setting
  command(DATACOMMANDSETTING_READWRITEMODE_WRITE |
          DATACOMMANDSETTING_ADDRESSMODE_AUTOMATIC);

  // transfer display data
  commandStart();

  commandTransfer((uint8_t)(ADRESSCOMMANDSETTING_DISPLAYADDRESS_BASE + firstDisplayAddress));

  for (auto n = 0u; n < min(NUM_OF_DISPLAYADDRESSES, numberOfData); n++) {
    commandTransfer(dataSequence[n], bitOrder);
  }

  commandStop();
}
