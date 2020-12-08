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

#ifndef TM1637_7SegmentLEDController_h
#define TM1637_7SegmentLEDController_h

#include <float.h>
#include "TM1637Controller.h"
#include "TM1637_7SegmentLEDController_SegmentAddressing.h"

#if PLATFORM_RASPBERRY_PI
#include <stdio.h>
#include <cmath>
using std::isnan;
using std::isinf;
#endif

template <
  size_t NUM_OF_DIGITS,
  size_t NUM_OF_GRIDS_FOR_USE,
  typename TSegmentAddressing
>
class TM1637_7SegmentLEDCustomSegmentAddressingController : public TM1637Controller
{
  static_assert(0 < NUM_OF_DIGITS && NUM_OF_DIGITS <= TM1637Controller::NUM_OF_GRIDS, "NUM_OF_DIGITS must be in range of 1~6");
  static_assert(0 < NUM_OF_GRIDS_FOR_USE && NUM_OF_GRIDS_FOR_USE <= TM1637Controller::NUM_OF_GRIDS, "NUM_OF_GRIDS_FOR_USE must be in range of 1~6");
  static_assert(NUM_OF_DIGITS <= NUM_OF_GRIDS_FOR_USE, "NUM_OF_DIGITS must be less than or equals to NUM_OF_GRIDS_FOR_USE");

  public:
    // XXX: requires <type_traits>
    //using integer_t = std::conditional<5 <= NUM_OF_DIGITS, int_fast32_t, int_fast16_t>::type;
    using integer_t = int_fast32_t;
    using float_t = float;

    TM1637_7SegmentLEDCustomSegmentAddressingController(
      uint8_t pinDIO,
      uint8_t pinCLK
    );

    TM1637_7SegmentLEDCustomSegmentAddressingController(
      uint8_t pinDIO,
      uint8_t pinCLK,
      const unsigned int (&gridsOrder)[NUM_OF_GRIDS]
    );

    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfGridsForUse() { return NUM_OF_GRIDS_FOR_USE; }
    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfDigits() { return NUM_OF_DIGITS; }

    static constexpr inline _ATTR_ALWAYS_INLINE_ integer_t displayableMaximumInteger() { return (integer_t)pow(10.0, NUM_OF_DIGITS) - 1l; }
    static constexpr inline _ATTR_ALWAYS_INLINE_ integer_t displayableMinimumInteger() { return 1l - (integer_t)pow(10.0, NUM_OF_DIGITS - 1); }

    static constexpr inline _ATTR_ALWAYS_INLINE_ float_t displayableMaximumPlusFloat() { return (float_t)displayableMaximumInteger(); }
    static constexpr inline _ATTR_ALWAYS_INLINE_ float_t displayableMinimumPlusFloat() { return (float_t)pow(10.0, 1.0 - NUM_OF_DIGITS); }

    static constexpr inline _ATTR_ALWAYS_INLINE_ float_t displayableMaximumMinusFloat() { return (float_t)displayableMinimumInteger(); }
    static constexpr inline _ATTR_ALWAYS_INLINE_ float_t displayableMinimumMinusFloat() { return (float_t)-pow(10.0, 2.0 - NUM_OF_DIGITS); }

    void clear(const bool flush = true);
    void clearCharacterSegments(const bool flush = true);
    void clearDecimalPointSegments(const bool flush = true);

    inline _ATTR_ALWAYS_INLINE_ void flush() { flushAllGrids(); }

    // operations for per digit
    void setSegmentBitsAt(const unsigned int digit, const uint8_t segmentBits, const bool flush = true);
    void switchSegmentBitsAt(const unsigned int digit, const uint8_t segmentBits, const bool trueForOnOtherwiseOff, const bool flush = true);

    inline _ATTR_ALWAYS_INLINE_ void setDecimalNumberAt(const unsigned int digit, const uint8_t decimalNumber, const bool flush = true);
    inline _ATTR_ALWAYS_INLINE_ void setHexNumberAt(const unsigned int digit, const uint8_t hexadecimalNumber, const bool flush = true);
    inline _ATTR_ALWAYS_INLINE_ void setDecimalPointOnAt(const unsigned int digit, const bool flush = true) { setDecimalPointAt(digit, true, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setDecimalPointOffAt(const unsigned int digit, const bool flush = true) { setDecimalPointAt(digit, false, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setDecimalPointAt(const unsigned int digit, const bool trueForOnOtherwiseOff, const bool flush = true);

    // operations for entire digits
    inline _ATTR_ALWAYS_INLINE_ void displaySegmentBits(const uint8_t (&segmentBits)[NUM_OF_GRIDS_FOR_USE], const bool flush = true);

    inline _ATTR_ALWAYS_INLINE_ void display(const integer_t value, const bool flush = true);
    inline _ATTR_ALWAYS_INLINE_ void displayZeroPadding(const integer_t value, const bool flush = true);
    inline _ATTR_ALWAYS_INLINE_ void displayHex(const integer_t value, const bool flush = true);
    inline _ATTR_ALWAYS_INLINE_ void displayHexZeroPadding(const integer_t value, const bool flush = true);
#if !SWIG
    void display(const char* const format, const integer_t value, const bool flush = true);
#endif

    inline _ATTR_ALWAYS_INLINE_ void display(const float_t value, const bool flush = true) { display(value, NUM_OF_DIGITS, NUM_OF_DIGITS, flush); }
    void display(const float_t value, const int width, const unsigned int precision, const bool flush = true);

#if !(PLATFORM_RASPBERRY_PI || SWIG)
    inline _ATTR_ALWAYS_INLINE_ void displayNumericalString(const String& str, const bool flush = true) { displayNumericalString(const_cast<char*>(str.c_str()), str.length(), flush); }
#endif
    void displayNumericalString(const char* const str, const size_t length, const bool flush = true);

  protected:
    void setSegmentBitsAtGrid(const unsigned int grid, const uint8_t segmentBits, const bool flush = true);
    void switchSegmentBitsAtGrid(const unsigned int grid, const uint8_t segmentBits, const bool trueForOnOtherwiseOff, const bool flush = true);
    inline _ATTR_ALWAYS_INLINE_ void flushAllGrids();

  private:
    using index_t = unsigned int;

    inline _ATTR_ALWAYS_INLINE_ const index_t& getGrid(const index_t& grid) { return m_gridsOrder[grid]; }
    inline _ATTR_ALWAYS_INLINE_ void writeSegmentBitsUnchecked(const index_t& grid, const uint8_t& segmentBits) { m_segmentBits[getGrid(grid)] = segmentBits; }
    inline _ATTR_ALWAYS_INLINE_ const uint8_t& readSegmentBitsUnchecked(const index_t& grid) { return m_segmentBits[getGrid(grid)]; }

    /*const*/ index_t m_gridsOrder[NUM_OF_GRIDS];
    uint8_t m_segmentBits[NUM_OF_GRIDS_FOR_USE] = {0};
};

template <size_t NUM_OF_DIGITS>
using TM1637_7SegmentLEDController = TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_DIGITS, StandardSegmentAddressing>;

using TM1637_1Digit7SegmentLEDController = TM1637_7SegmentLEDController<1 /*DIGITS*/>;
using TM1637_2Digit7SegmentLEDController = TM1637_7SegmentLEDController<2 /*DIGITS*/>;
using TM1637_3Digit7SegmentLEDController = TM1637_7SegmentLEDController<3 /*DIGITS*/>;
using TM1637_4Digit7SegmentLEDController = TM1637_7SegmentLEDController<4 /*DIGITS*/>;
using TM1637_5Digit7SegmentLEDController = TM1637_7SegmentLEDController<5 /*DIGITS*/>;
using TM1637_6Digit7SegmentLEDController = TM1637_7SegmentLEDController<6 /*DIGITS*/>;

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::TM1637_7SegmentLEDCustomSegmentAddressingController(
  uint8_t pinDIO,
  uint8_t pinCLK
) : TM1637Controller(pinDIO, pinCLK)
{
  for (auto grid = 0u; grid < NUM_OF_GRIDS; grid++)
    m_gridsOrder[grid] = grid; // set default grids order
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::TM1637_7SegmentLEDCustomSegmentAddressingController(
  uint8_t pinDIO,
  uint8_t pinCLK,
  const unsigned int (&gridsOrder)[NUM_OF_GRIDS]
) : TM1637Controller(pinDIO, pinCLK)
{
  for (auto grid = 0u; grid < NUM_OF_GRIDS; grid++) {
    if (gridsOrder[grid] < NUM_OF_GRIDS)
      m_gridsOrder[grid] = gridsOrder[grid];
    else
      m_gridsOrder[grid] = grid; // out of range; set default value instead of specified one
  }
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::clear(bool flush)
{
  for (auto grid = 0u; grid < NUM_OF_GRIDS_FOR_USE; grid++)
    writeSegmentBitsUnchecked(grid, 0b00000000);

  if (flush)
    flushAllGrids();
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::clearCharacterSegments(bool flush)
{
  for (auto grid = 0u; grid < NUM_OF_GRIDS_FOR_USE; grid++)
    writeSegmentBitsUnchecked(grid, readSegmentBitsUnchecked(grid) & TSegmentAddressing::SEGMENTBITS_MASK_DECIMALPOINT);

  if (flush)
    flushAllGrids();
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::clearDecimalPointSegments(bool flush)
{
  for (auto grid = 0u; grid < NUM_OF_GRIDS_FOR_USE; grid++)
    writeSegmentBitsUnchecked(grid, readSegmentBitsUnchecked(grid) & TSegmentAddressing::SEGMENTBITS_MASK_CHARACTER);

  if (flush)
    flushAllGrids();
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::flushAllGrids()
{
  this->transferDataToAddressAutomatic(m_segmentBits, NUM_OF_GRIDS_FOR_USE, LSBFIRST, 0);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::setSegmentBitsAtGrid(
  const unsigned int grid,
  const uint8_t segmentBits,
  const bool flush
)
{
  if (NUM_OF_GRIDS_FOR_USE <= grid)
    return; // out of range

  writeSegmentBitsUnchecked(grid, segmentBits);

  if (flush)
    this->transferDataToAddressFixed(readSegmentBitsUnchecked(grid), LSBFIRST, getGrid(grid));
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::switchSegmentBitsAtGrid(
  const unsigned int grid,
  const uint8_t segmentBits,
  const bool trueForOnOtherwiseOff,
  const bool flush
)
{
  if (NUM_OF_GRIDS_FOR_USE <= grid)
    return; // out of range

  writeSegmentBitsUnchecked(
    grid,
    trueForOnOtherwiseOff
      ? readSegmentBitsUnchecked(grid) | segmentBits
      : readSegmentBitsUnchecked(grid) & ~segmentBits
  );

  if (flush)
    this->transferDataToAddressFixed(readSegmentBitsUnchecked(grid), LSBFIRST, getGrid(grid));
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::setSegmentBitsAt(
  const unsigned int digit,
  const uint8_t segmentBits,
  const bool flush
)
{
  if (NUM_OF_DIGITS <= digit)
    return; // out of range

  writeSegmentBitsUnchecked(digit, segmentBits);

  if (flush)
    this->transferDataToAddressFixed(readSegmentBitsUnchecked(digit), LSBFIRST, getGrid(digit));
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::switchSegmentBitsAt(
  const unsigned int digit,
  const uint8_t segmentBits,
  const bool trueForOnOtherwiseOff,
  const bool flush
)
{
  if (NUM_OF_DIGITS <= digit)
    return; // out of range

  switchSegmentBitsAtGrid(digit, segmentBits, trueForOnOtherwiseOff, flush);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::setDecimalNumberAt(
  const unsigned int digit,
  const uint8_t decimalNumber,
  const bool flush
)
{
  if (NUM_OF_DIGITS <= digit)
    return; // out of range
  if (10 <= decimalNumber)
    return; // out of range

  setSegmentBitsAt(
    digit,
    (readSegmentBitsUnchecked(digit) & TSegmentAddressing::SEGMENTBITS_MASK_DECIMALPOINT) | TSegmentAddressing::CHARS_HEXADECIMALS[decimalNumber],
    flush
  );
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::setHexNumberAt(
  const unsigned int digit,
  const uint8_t hexadecimalNumber,
  const bool flush
)
{
  if (NUM_OF_DIGITS <= digit)
    return; // out of range
  if (0x10 <= hexadecimalNumber)
    return; // out of range

  setSegmentBitsAt(
    digit,
    (readSegmentBitsUnchecked(digit) & TSegmentAddressing::SEGMENTBITS_MASK_DECIMALPOINT) | TSegmentAddressing::CHARS_HEXADECIMALS[hexadecimalNumber],
    flush
  );
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::setDecimalPointAt(
  const unsigned int digit,
  const bool trueForOnOtherwiseOff,
  const bool flush
)
{
  switchSegmentBitsAt(digit, TSegmentAddressing::SEGMENTBITS_MASK_DECIMALPOINT, trueForOnOtherwiseOff, flush);
}



template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::displaySegmentBits(
  const uint8_t (&segmentBits)[NUM_OF_GRIDS_FOR_USE],
  const bool flush
)
{
  for (auto grid = 0u; grid < NUM_OF_GRIDS_FOR_USE; grid++)
    writeSegmentBitsUnchecked(grid, segmentBits[grid]);

  if (flush)
    flushAllGrids();
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::display(
  const integer_t value,
  const bool flush
)
{
  constexpr char format[] = {'%', (char)('0' + NUM_OF_DIGITS), 'l', 'd', '\0'}; // "%nld"

  display(format, value, flush);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::displayZeroPadding(
  const integer_t value,
  const bool flush
)
{
  constexpr char format[] = {'%', '0', (char)('0' + NUM_OF_DIGITS), 'l', 'd', '\0'}; // "%0nld"

  display(format, value, flush);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::displayHex(
  const integer_t value,
  const bool flush
)
{
  constexpr char format[] = {'%', (char)('0' + NUM_OF_DIGITS), 'l', 'x', '\0'}; // "%nlx"

  display(format, value, flush);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::displayHexZeroPadding(
  const integer_t value,
  const bool flush
)
{
  constexpr char format[] = {'%', '0', (char)('0' + NUM_OF_DIGITS), 'l', 'x', '\0'}; // "%0nlx"

  display(format, value, flush);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::display(
  const char* const format,
  const integer_t value,
  const bool flush
)
{
  char str[NUM_OF_DIGITS + 1] = { '\0' };

  snprintf(str, sizeof(str), format, value);

  displayNumericalString(str, NUM_OF_DIGITS + 1, flush);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::display(
  const float_t value,
  const int width,
  const unsigned int precision,
  const bool flush
)
{
  constexpr bool noFlush = false;

  // (+/-)inifinity
  if (isinf(value)) {
    clear(noFlush);

    if (0.0f < value) {
      setSegmentBitsAt(0, TSegmentAddressing::CHARS_I_OF_INF, noFlush);
      setSegmentBitsAt(1, TSegmentAddressing::CHARS_N_OF_INF, noFlush);
      setSegmentBitsAt(2, TSegmentAddressing::CHARS_F_OF_INF, noFlush);
      setDecimalPointOnAt(2);
    }
    else {
      setSegmentBitsAt(0, TSegmentAddressing::CHARS_MINUS, noFlush);
      setSegmentBitsAt(1, TSegmentAddressing::CHARS_I_OF_INF, noFlush);
      setSegmentBitsAt(2, TSegmentAddressing::CHARS_N_OF_INF, noFlush);
      setSegmentBitsAt(3, TSegmentAddressing::CHARS_F_OF_INF, noFlush);
      setDecimalPointOnAt(3);
    }

    if (flush)
      flushAllGrids();

    return;
  }

  // NaN
  if (isnan(value)) {
    clear(noFlush);

    setSegmentBitsAt(0, TSegmentAddressing::CHARS_N_OF_NAN, noFlush);
    setSegmentBitsAt(1, TSegmentAddressing::CHARS_A_OF_NAN, noFlush);
    setSegmentBitsAt(2, TSegmentAddressing::CHARS_N_OF_NAN, noFlush);
    setDecimalPointOnAt(2);

    if (flush)
      flushAllGrids();

    return;
  }

  constexpr size_t len = 20;
  char str[len] = { '\0' };

#if PLATFORM_RASPBERRY_PI
  char format[8] = { '\0' };

  if (!(-(int)NUM_OF_DIGITS <= width && width <= (int)NUM_OF_DIGITS) || NUM_OF_DIGITS < precision)
    return; // XXX: diplays nothing

  snprintf(format, sizeof(format), "%%%d.%df", width, precision); // "%x.xf"
  snprintf(str, sizeof(str), format, value);
#else
  // XXX: Arduino does not support %f, %g, %e
  if (0 == precision)
    dtostrf(value, NUM_OF_DIGITS, 0, str);
  else
    dtostrf(value, NUM_OF_DIGITS + 1/* decimal point*/, precision, str);
#endif

  displayNumericalString(str, len, flush);
}

template <size_t NUM_OF_DIGITS, size_t NUM_OF_GRIDS_FOR_USE, typename TSegmentAddressing>
void TM1637_7SegmentLEDCustomSegmentAddressingController<NUM_OF_DIGITS, NUM_OF_GRIDS_FOR_USE, TSegmentAddressing>::displayNumericalString(
  const char* const str,
  const size_t length,
  const bool flush
)
{
  constexpr bool noFlush = false;

  clear(noFlush);

  if (nullptr == str)
    return;

  auto index = 0u;

  for (auto digit = 0u;; digit++) {
    if (length <= index)
      break;

    auto c = str[index++];

    if ('.' == c) {
      setDecimalPointOnAt(--digit, noFlush);
      continue;
    }

    if (NUM_OF_DIGITS <= digit)
      break;

    if ('0' <= c && c <= '9')
      setDecimalNumberAt(digit, c - '0', noFlush);
    else if ('A' <= c && c <= 'F')
      setHexNumberAt(digit, 0xA + c - 'A', noFlush);
    else if ('a' <= c && c <= 'f')
      setHexNumberAt(digit, 0xA + c - 'a', noFlush);
    else if ('-' == c)
      setSegmentBitsAtGrid(digit, TSegmentAddressing::CHARS_MINUS, noFlush);
    else
      setSegmentBitsAtGrid(digit, TSegmentAddressing::CHARS_SPACE, noFlush);
  }

  if (flush)
    flushAllGrids();
}

#endif // TM1637_7SegmentLEDController_h
