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

#ifndef TM1637_OSL40391IXController_h
#define TM1637_OSL40391IXController_h

#include "TM1637_7SegmentLEDController.h"
#include "TM1637_OSL40391IXController_SegmentAddressing.h"

template <typename TSegmentAddressing>
using TM1637_4Digit5Grid7SegmentLEDCustomSegmentAddressingController = TM1637_7SegmentLEDCustomSegmentAddressingController<4 /*DIGITS*/, 5 /* GRIDS (GRID-5 for extra segments) */, TSegmentAddressing>;

template <typename TSegmentAddressing>
class TM1637_OSL40391IXCustomSegmentAddressingController
  : public TM1637_4Digit5Grid7SegmentLEDCustomSegmentAddressingController<TSegmentAddressing>
{
  protected:
    using float_t = typename TM1637_4Digit5Grid7SegmentLEDCustomSegmentAddressingController<TSegmentAddressing>::float_t;

    static constexpr inline _ATTR_ALWAYS_INLINE_ int gridForDots() { return TM1637_4Digit5Grid7SegmentLEDCustomSegmentAddressingController<TSegmentAddressing>::numberOfGridsForUse() - 1; }

  public:
    TM1637_OSL40391IXCustomSegmentAddressingController(
      uint8_t pinDIO,
      uint8_t pinCLK
    )
      : TM1637_4Digit5Grid7SegmentLEDCustomSegmentAddressingController<TSegmentAddressing>(pinDIO, pinCLK) {}

    TM1637_OSL40391IXCustomSegmentAddressingController(
      uint8_t pinDIO,
      uint8_t pinCLK,
      const unsigned int (&gridsOrder)[TM1637Controller::NUM_OF_GRIDS]
    )
      : TM1637_4Digit5Grid7SegmentLEDCustomSegmentAddressingController<TSegmentAddressing>(pinDIO, pinCLK, gridsOrder) {}

    inline _ATTR_ALWAYS_INLINE_ void setColonOn(const bool flush = true) { setColon(true, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setColonOff(const bool flush = true) { setColon(false, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setColon(const bool trueForOnOtherwiseOff, const bool flush = true) { this->switchSegmentBitsAtGrid(gridForDots(), TSegmentAddressing::SEGMENTBITS_COLON, trueForOnOtherwiseOff, flush); }

    inline _ATTR_ALWAYS_INLINE_ void setUpperDotOfColonOn(const bool flush = true) { setUpperDotOfColon(true, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setUpperDotOfColonOff(const bool flush = true) { setUpperDotOfColon(false, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setUpperDotOfColon(const bool trueForOnOtherwiseOff, const bool flush = true) { this->switchSegmentBitsAtGrid(gridForDots(), TSegmentAddressing::SEGMENTBITS_COLON_UPPER, trueForOnOtherwiseOff, flush); }

    inline _ATTR_ALWAYS_INLINE_ void setLowerDotOfColonOn(const bool flush = true) { setLowerDotOfColon(true, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setLowerDotOfColonOff(const bool flush = true) { setLowerDotOfColon(false, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setLowerDotOfColon(const bool trueForOnOtherwiseOff, const bool flush = true) { this->switchSegmentBitsAtGrid(gridForDots(), TSegmentAddressing::SEGMENTBITS_COLON_LOWER, trueForOnOtherwiseOff, flush); }

    inline _ATTR_ALWAYS_INLINE_ void setDegreeSignOn(const bool flush = true) { setDegreeSign(true, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setDegreeSignOff(const bool flush = true) { setDegreeSign(false, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setDegreeSign(bool trueForOnOtherwiseOff, const bool flush = true) { this->switchSegmentBitsAtGrid(gridForDots(), TSegmentAddressing::SEGMENTBITS_DEGREESIGN, trueForOnOtherwiseOff, flush); }

    inline _ATTR_ALWAYS_INLINE_ void setPercent(const bool flush = true);

    inline _ATTR_ALWAYS_INLINE_ void displayTemperatureCelsius(const float temperatureCelsius, const bool flush = true) { displayTemperature(temperatureCelsius, true, flush); }
    inline _ATTR_ALWAYS_INLINE_ void displayTemperatureFahrenheit(const float temperatureFahrenheit, const bool flush = true)  { displayTemperature(temperatureFahrenheit, false, flush); }
    void displayTemperature(const float temperature, const bool trueForCelsiusOtherwiseFahrenheit, const bool flush = true);

    void displayPercent(const float value, const bool flush = true);

    inline _ATTR_ALWAYS_INLINE_ void displayTimeOfDayMinutesSeconds(const uint32_t timeInMilliseconds, const bool blinkColon = true, const bool flush = true) { displayElapsedTimeMinutesSeconds(timeInMilliseconds % millisecondsPerHour); }
    inline _ATTR_ALWAYS_INLINE_ void displayTimeOfDayHoursMinutes(const uint32_t timeInMilliseconds, const bool blinkColon = true, const bool flush = true) { displayElapsedTimeHoursMinutes(timeInMilliseconds % millisecondsPerDay); }
    void displayElapsedTimeMinutesSeconds(const uint32_t elapsedMilliseconds, const bool blinkColon = true, const bool flush = true);
    void displayElapsedTimeHoursMinutes(const uint32_t elapsedMilliseconds, const bool blinkColon = true, const bool flush = true);

  protected:
    void displayOutOfRange(const bool flush = true);

  private:
    static constexpr float_t displayableMaximumFloatWithUnit = 999.f;
    static constexpr float_t displayableMinimumFloatWithUnit = -99.f;
    static constexpr uint32_t millisecondsPerHour = 60ul * 60ul * 1000ul;
    static constexpr uint32_t millisecondsPerDay = 24ul * millisecondsPerHour;
};

using TM1637_OSL40391IXController = TM1637_OSL40391IXCustomSegmentAddressingController<OSL40391IXStandardSegmentAddressing>;

template <typename TSegmentAddressing>
void TM1637_OSL40391IXCustomSegmentAddressingController<TSegmentAddressing>::setPercent(const bool flush)
{
  constexpr bool noFlush = false;

  this->setSegmentBitsAt(this->numberOfDigits() - 1, TSegmentAddressing::CHARS_PERCENT, noFlush);

  setDegreeSign(true, noFlush);

  if (flush)
    this->flushAllGrids();
}

template <typename TSegmentAddressing>
void TM1637_OSL40391IXCustomSegmentAddressingController<TSegmentAddressing>::displayOutOfRange(const bool flush)
{
  constexpr bool noFlush = false;

  for (auto digit = 0u; digit < this->numberOfDigits(); digit++)
    this->setSegmentBitsAt(digit, TSegmentAddressing::CHARS_OUT_OF_RANGE, noFlush);

  if (flush)
    this->flushAllGrids();
}

template <typename TSegmentAddressing>
void TM1637_OSL40391IXCustomSegmentAddressingController<TSegmentAddressing>::displayTemperature(
  const float temperature,
  const bool trueForCelsiusOtherwiseFahrenheit,
  const bool flush
)
{
  constexpr bool noFlush = false;

  this->clear(noFlush);

  if (!(displayableMinimumFloatWithUnit <= temperature && temperature <= displayableMaximumFloatWithUnit ) ||
      isnan(temperature) ||
      isinf(temperature)) {
    // out of displayable range, (+/-)INF, NaN
    displayOutOfRange(noFlush);
  }
  else {
    this->display(temperature, noFlush);
    this->setDecimalPointOffAt(this->numberOfDigits() - 2, noFlush);
  }

  if (trueForCelsiusOtherwiseFahrenheit)
    this->setHexNumberAt(this->numberOfDigits() - 1, 0xC, noFlush); // 'C'
  else
    this->setHexNumberAt(this->numberOfDigits() - 1, 0xF, noFlush); // 'F'

  setDegreeSignOn(noFlush); // °

  if (flush)
    this->flushAllGrids();
}

template <typename TSegmentAddressing>
void TM1637_OSL40391IXCustomSegmentAddressingController<TSegmentAddressing>::displayPercent(
  const float value,
  const bool flush
)
{
  constexpr bool noFlush = false;

  if (!(displayableMinimumFloatWithUnit <= value && value <= displayableMaximumFloatWithUnit ) ||
      isnan(value) ||
      isinf(value)) {
    // out of displayable range, (+/-)INF, NaN
    displayOutOfRange(noFlush);
  }
  else {
    this->display(value, noFlush);
    this->setDecimalPointOffAt(this->numberOfDigits() - 2, noFlush);
  }

  setPercent(noFlush);

  if (flush)
    this->flushAllGrids();
}

template <typename TSegmentAddressing>
void TM1637_OSL40391IXCustomSegmentAddressingController<TSegmentAddressing>::displayElapsedTimeMinutesSeconds(
  const uint32_t elapsedMilliseconds,
  const bool blinkColon,
  const bool flush
)
{
  constexpr bool noFlush = false;
  auto seconds = elapsedMilliseconds / 1000ul;
  auto minutes = (seconds / 60ul) % 100ul;

  this->display("%04d", minutes * 100ul + seconds % 60ul, noFlush);

  setColon(!blinkColon || (elapsedMilliseconds % 1000ul < 500ul), noFlush);

  if (flush)
    this->flushAllGrids();
}

template <typename TSegmentAddressing>
void TM1637_OSL40391IXCustomSegmentAddressingController<TSegmentAddressing>::displayElapsedTimeHoursMinutes(
  const uint32_t elapsedMilliseconds,
  const bool blinkColon,
  const bool flush
)
{
  constexpr bool noFlush = false;
  auto seconds = elapsedMilliseconds / 1000ul;
  auto minutes = (seconds / 60ul) % 60ul;
  auto hours = (seconds / 3600ul) % 100ul;

  this->display("%04d", (long)(hours * 100ul + minutes), noFlush);

  setColon(!blinkColon || (elapsedMilliseconds % 1000ul < 500ul), noFlush);

  if (flush)
    this->flushAllGrids();
}

#endif // TM1637_OSL40391IXController_h
