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

#ifndef TM1637_DotMatrixLEDController_h
#define TM1637_DotMatrixLEDController_h

#include "TM1637Controller.h"

template <
  size_t NUM_OF_ANODE_LINES,  // = number of anode pins
  size_t NUM_OF_CATHODE_LINES // = number of cathode pins
>
class TM1637_DotMatrixLEDController
  : public TM1637Controller
{
  static_assert(0 < NUM_OF_ANODE_LINES && NUM_OF_ANODE_LINES <= TM1637Controller::NUM_OF_GRIDS, "NUM_OF_ANODE_LINES must be in range of 1~6");
  static_assert(0 < NUM_OF_CATHODE_LINES && NUM_OF_CATHODE_LINES <= TM1637Controller::NUM_BITS_PER_GRID, "NUM_OF_CATHODE_LINES must be in range of 1~8");

  public:
    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfAnodeLines() { return NUM_OF_ANODE_LINES; }
    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfCathodeLines() { return NUM_OF_CATHODE_LINES; }

    void fill(const bool flush = true);
    void clear(const bool flush = true);
    void invert(const bool flush = true);
    inline _ATTR_ALWAYS_INLINE_ void flush() const { flushAllAnodeLines(); }

    virtual void fillRow(const unsigned int row, const bool flush = true)  = 0;
    virtual void clearRow(const unsigned int row, const bool flush = true) = 0;

    virtual void fillColumn(const unsigned int column, const bool flush = true)  = 0;
    virtual void clearColumn(const unsigned int column, const bool flush = true) = 0;

    inline _ATTR_ALWAYS_INLINE_ void setOn(const unsigned int column, const unsigned int row, const bool flush = true) { set(column, row, true, flush); }
    inline _ATTR_ALWAYS_INLINE_ void setOff(const unsigned int column, const unsigned int row, const bool flush = true) { set(column, row, false, flush); }
    virtual void set(const unsigned int column, const unsigned int row, const bool trueForOnOtherwiseOff, const bool flush = true) = 0;

  protected:
    TM1637_DotMatrixLEDController(
      uint8_t pinDIO,
      uint8_t pinCLK
    ) : TM1637Controller(pinDIO, pinCLK) {}

    void fillAnodeLine(const unsigned int line, const bool flush = true);
    void clearAnodeLine(const unsigned int line, const bool flush = true);

    void fillCathodeLine(const unsigned int line, const bool flush = true);
    void clearCathodeLine(const unsigned int line, const bool flush = true);

    void setAt(const unsigned int cathodeLine, const unsigned int anodeLine, const bool trueForOnOtherwiseOff, const bool flush = true);

    void setWithBitmap(const uint8_t (&bitmap)[NUM_OF_ANODE_LINES], const bool flush = true);
    void setWithBitmapFlipVertical(const uint8_t (&bitmap)[NUM_OF_ANODE_LINES], const bool flush = true);
    void setWithBitmapRotate90(const uint8_t (&bitmap)[NUM_OF_CATHODE_LINES], const bool flush = true);
    void setWithBitmapRotate270(const uint8_t (&bitmap)[NUM_OF_CATHODE_LINES], const bool flush = true);

  private:
    static constexpr size_t BITS_OF_CATHODE_LINES = TM1637Controller::NUM_BITS_PER_GRID;
    static constexpr uint8_t AVAILABLE_CATHODE_LINE_MASK = (uint8_t)(0xffu << (BITS_OF_CATHODE_LINES - NUM_OF_CATHODE_LINES));
    static constexpr uint8_t BIT_CATHODE_LINE0 = 1u << (BITS_OF_CATHODE_LINES - 1);

    inline _ATTR_ALWAYS_INLINE_ void flushAllAnodeLines() const;
    inline _ATTR_ALWAYS_INLINE_ void flushAnodeLine(const unsigned int line) const;

    uint8_t m_anodeLineBits[NUM_OF_ANODE_LINES] = {0}; // in MSBFIRST order
};

template <
  size_t NUM_OF_COLS, // must be in range of 1~8
  size_t NUM_OF_ROWS  // must be in range of 1~NUMBER_OF_GRIDS(6)
>
class TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController
  : public TM1637_DotMatrixLEDController<NUM_OF_ROWS, NUM_OF_COLS>
{
  static_assert(0 < NUM_OF_ROWS && NUM_OF_ROWS <= TM1637Controller::NUM_OF_GRIDS, "NUM_OF_ROWS must be in range of 1~6");
  static_assert(0 < NUM_OF_COLS && NUM_OF_COLS <= TM1637Controller::NUM_BITS_PER_GRID, "NUM_OF_COLS must be in range of 1~8");

  public:
    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfRows() { return NUM_OF_ROWS; }
    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfColumns() { return NUM_OF_COLS; }

    TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController(
      uint8_t pinDIO,
      uint8_t pinCLK
    ) : TM1637_DotMatrixLEDController<NUM_OF_ROWS, NUM_OF_COLS>(pinDIO, pinCLK) {}

    inline _ATTR_ALWAYS_INLINE_ void fillRow(const unsigned int row, const bool flush = true) override { this->fillAnodeLine(row, flush); }
    inline _ATTR_ALWAYS_INLINE_ void clearRow(const unsigned int row, const bool flush = true) override { this->clearAnodeLine(row, flush); }

    inline _ATTR_ALWAYS_INLINE_ void fillColumn(const unsigned int column, const bool flush = true) override { this->fillCathodeLine(column, flush); }
    inline _ATTR_ALWAYS_INLINE_ void clearColumn(const unsigned int column, const bool flush = true) override { this->clearCathodeLine(column, flush); }

    void set(const unsigned int column, const unsigned int row, const bool trueForOnOtherwiseOff, const bool flush = true) override { this->setAt(column, row, trueForOnOtherwiseOff, flush); }

    inline _ATTR_ALWAYS_INLINE_ void draw(const uint8_t (&bitmapTopLeftOrigin)[NUM_OF_ROWS], const bool flush = true) { this->setWithBitmap(bitmapTopLeftOrigin, flush); }
    inline _ATTR_ALWAYS_INLINE_ void drawRotated(const uint8_t (&bitmapBottomLeftOrigin)[NUM_OF_COLS], const bool flush = true) { this->setWithBitmapRotate90(bitmapBottomLeftOrigin, flush); }
};

using TM1637_8CathodeColumns6AnodeRowsDotMatrixLEDController = TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<8, 6>;
using TM1637_7CathodeColumns5AnodeRowsDotMatrixLEDController = TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<7, 5>;
using TM1637_4CathodeColumns4AnodeRowsDotMatrixLEDController = TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<4, 4>;
using TM1637_3CathodeColumns3AnodeRowsDotMatrixLEDController = TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<3, 3>;
using TM1637_2CathodeColumns2AnodeRowsDotMatrixLEDController = TM1637_CathodeColumnsAnodeRowsDotMatrixLEDController<2, 2>;

template <
  size_t NUM_OF_COLS, // must be in range of 1~NUMBER_OF_GRIDS(6)
  size_t NUM_OF_ROWS  // must be in range of 1~8
>
class TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController
  : public TM1637_DotMatrixLEDController<NUM_OF_COLS, NUM_OF_ROWS>
{
  static_assert(0 < NUM_OF_ROWS && NUM_OF_ROWS <= TM1637Controller::NUM_BITS_PER_GRID, "NUM_OF_ROWS must be in range of 1~8");
  static_assert(0 < NUM_OF_COLS && NUM_OF_COLS <= TM1637Controller::NUM_OF_GRIDS, "NUM_OF_COLS must be in range of 1~6");

  public:
    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfRows() { return NUM_OF_ROWS; }
    static constexpr inline _ATTR_ALWAYS_INLINE_ size_t numberOfColumns() { return NUM_OF_COLS; }

    TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController(
      uint8_t pinDIO,
      uint8_t pinCLK
    ) : TM1637_DotMatrixLEDController<NUM_OF_COLS, NUM_OF_ROWS>(pinDIO, pinCLK) {}

    inline _ATTR_ALWAYS_INLINE_ void fillRow(const unsigned int row, const bool flush = true) override { this->fillCathodeLine(row, flush); }
    inline _ATTR_ALWAYS_INLINE_ void clearRow(const unsigned int row, const bool flush = true) override { this->clearCathodeLine(row, flush); }

    inline _ATTR_ALWAYS_INLINE_ void fillColumn(const unsigned int column, const bool flush = true) override { this->fillAnodeLine(column, flush); }
    inline _ATTR_ALWAYS_INLINE_ void clearColumn(const unsigned int column, const bool flush = true) override { this->clearAnodeLine(column, flush); }

    void set(const unsigned int column, const unsigned int row, const bool trueForOnOtherwiseOff, const bool flush = true) override { this->setAt(row, column, trueForOnOtherwiseOff, flush); }

    inline _ATTR_ALWAYS_INLINE_ void draw(const uint8_t (&bitmapTopLeftOrigin)[NUM_OF_ROWS], const bool flush = true) { this->setWithBitmapRotate270(bitmapTopLeftOrigin, flush); }
    inline _ATTR_ALWAYS_INLINE_ void drawRotated(const uint8_t (&bitmapBottomLeftOrigin)[NUM_OF_COLS], const bool flush = true) { this->setWithBitmapFlipVertical(bitmapBottomLeftOrigin, flush); }
};

using TM1637_6AnodeColumns8CathodeRowsDotMatrixLEDController = TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<6, 8>;
using TM1637_5AnodeColumns7CathodeRowsDotMatrixLEDController = TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<5, 7>;
using TM1637_4AnodeColumns4CathodeRowsDotMatrixLEDController = TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<4, 4>;
using TM1637_3AnodeColumns3CathodeRowsDotMatrixLEDController = TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<3, 3>;
using TM1637_2AnodeColumns2CathodeRowsDotMatrixLEDController = TM1637_AnodeColumnsCathodeRowsDotMatrixLEDController<2, 2>;

/*
 * TM1637_DotMatrixLEDController
 */
template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::flushAllAnodeLines() const
{
  this->transferDataToAddressAutomatic(m_anodeLineBits, NUM_OF_ANODE_LINES, MSBFIRST, 0);
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::flushAnodeLine(const unsigned int line) const
{
  this->transferDataToAddressFixed(m_anodeLineBits[line], MSBFIRST, line);
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::fill(const bool flush)
{
  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++)
    m_anodeLineBits[al] = 0b11111111u & AVAILABLE_CATHODE_LINE_MASK;

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::clear(const bool flush)
{
  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++)
    m_anodeLineBits[al] = 0b00000000u;

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::invert(const bool flush)
{
  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++)
    m_anodeLineBits[al] = ~m_anodeLineBits[al] & AVAILABLE_CATHODE_LINE_MASK;

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::fillAnodeLine(const unsigned int line, const bool flush)
{
  if (NUM_OF_ANODE_LINES <= line)
    return; // out of range

  m_anodeLineBits[line] = 0b11111111u & AVAILABLE_CATHODE_LINE_MASK;

  if (flush)
    flushAnodeLine(line);
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::clearAnodeLine(const unsigned int line, const bool flush)
{
  if (NUM_OF_ANODE_LINES <= line)
    return; // out of range

  m_anodeLineBits[line] = 0b00000000u;

  if (flush)
    flushAnodeLine(line);
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::fillCathodeLine(const unsigned int line, const bool flush)
{
  if (NUM_OF_CATHODE_LINES <= line)
    return; // out of range

  uint8_t mask = BIT_CATHODE_LINE0 >> line;

  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++)
    m_anodeLineBits[al] |= mask;

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::clearCathodeLine(const unsigned int line, const bool flush)
{
  if (NUM_OF_CATHODE_LINES <= line)
    return; // out of range

  uint8_t mask = ~(BIT_CATHODE_LINE0 >> line);

  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++)
    m_anodeLineBits[al] &= mask;

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::setAt(
  const unsigned int cathodeLine,
  const unsigned int anodeLine,
  const bool trueForOnOtherwiseOff,
  const bool flush
)
{
  if (NUM_OF_CATHODE_LINES <= cathodeLine)
    return; // out of range
  if (NUM_OF_ANODE_LINES <= anodeLine)
    return; // out of range

  uint8_t mask = BIT_CATHODE_LINE0 >> cathodeLine;

  if (trueForOnOtherwiseOff)
    m_anodeLineBits[anodeLine] |= mask;
  else
    m_anodeLineBits[anodeLine] &= ~mask;

  if (flush)
    flushAnodeLine(anodeLine);
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::setWithBitmap(
  const uint8_t (&bitmap)[NUM_OF_ANODE_LINES],
  const bool flush
)
{
  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++)
    m_anodeLineBits[al] = bitmap[al] << (BITS_OF_CATHODE_LINES - NUM_OF_CATHODE_LINES);

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::setWithBitmapRotate90(
  const uint8_t (&bitmap)[NUM_OF_CATHODE_LINES],
  const bool flush
)
{
  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++) {
    uint8_t lineBits = 0u;

    for (auto cl = 0u; cl < NUM_OF_CATHODE_LINES; cl++)
      lineBits |= ((bitmap[cl] >> (NUM_OF_ANODE_LINES - 1 - al)) & 0b1) << (cl + BITS_OF_CATHODE_LINES - NUM_OF_CATHODE_LINES);

    m_anodeLineBits[al] = lineBits & AVAILABLE_CATHODE_LINE_MASK;
  }

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::setWithBitmapFlipVertical(
  const uint8_t (&bitmap)[NUM_OF_ANODE_LINES],
  const bool flush
)
{
  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++)
    m_anodeLineBits[al] = (bitmap[NUM_OF_ANODE_LINES - 1 - al] << (BITS_OF_CATHODE_LINES - NUM_OF_CATHODE_LINES)) & AVAILABLE_CATHODE_LINE_MASK;

  if (flush)
    flushAllAnodeLines();
}

template <size_t NUM_OF_ANODE_LINES, size_t NUM_OF_CATHODE_LINES>
void TM1637_DotMatrixLEDController<NUM_OF_ANODE_LINES, NUM_OF_CATHODE_LINES>::setWithBitmapRotate270(
  const uint8_t (&bitmap)[NUM_OF_CATHODE_LINES],
  const bool flush
)
{
  for (auto al = 0u; al < NUM_OF_ANODE_LINES; al++) {
    uint8_t lineBits = 0u;

    for (auto cl = 0u; cl < NUM_OF_CATHODE_LINES; cl++)
      lineBits |= ((bitmap[NUM_OF_CATHODE_LINES - 1 - cl] >> (NUM_OF_ANODE_LINES - 1 - al)) & 0b1) << (cl + BITS_OF_CATHODE_LINES - NUM_OF_CATHODE_LINES);

    m_anodeLineBits[al] = lineBits & AVAILABLE_CATHODE_LINE_MASK;
  }

  if (flush)
    flushAllAnodeLines();
}

#endif // TM1637_DotMatrixLEDController_h