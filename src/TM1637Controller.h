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

#ifndef TM1637Controller_h
#define TM1637Controller_h

#ifdef PLATFORM_RASPBERRY_PI
#include "WiringPi.h"
#else
#include <Arduino.h>
#endif

#include "TM1637ControllerCommands.h"

#if SWIG
#define _ATTR_ALWAYS_INLINE_
#else
#define _ATTR_ALWAYS_INLINE_ __attribute__ ((always_inline))
#endif

// data sheet:
//   http://akizukidenshi.com/download/ds/titanmicro/TM1637_V2.4_EN.PDF

class TM1637Controller : private TM1637ControllerCommands {
  protected:
    static constexpr size_t NUM_OF_GRIDS = 6;
    static constexpr size_t NUM_BITS_PER_GRID = 8;

  private:
    static constexpr size_t NUM_OF_DISPLAYADDRESSES = 6;

  protected:
    TM1637Controller(
      uint8_t pinDIO, // The pin number connected to TM1637's DIO (#17)
      uint8_t pinCLK  // The pin number connected to TM1637's CLK (#18)
    )
      : m_pinDIO(pinDIO),
        m_pinCLK(pinCLK)
    {}

  public:
    void begin(const unsigned int displayBrightnessPercent = 100);
    void reset() const;

    inline _ATTR_ALWAYS_INLINE_ void setDisplaySwitchOn()  { setDisplaySwitch(true); }
    inline _ATTR_ALWAYS_INLINE_ void setDisplaySwitchOff() { setDisplaySwitch(false); }
    inline _ATTR_ALWAYS_INLINE_ void setDisplaySwitch(const bool trueForOnOtherwiseOff)
    {
      setDisplayControl(
        (m_displayControl & ~DISPLAYCONTROL_DISPLAYSWITCH_MASK_) |
        (trueForOnOtherwiseOff ? DISPLAYCONTROL_DISPLAYSWITCH_ON : DISPLAYCONTROL_DISPLAYSWITCH_OFF)
      );
    }

    inline _ATTR_ALWAYS_INLINE_ bool getDisplaySwitch() const { return (bool)(m_displayControl & DISPLAYCONTROL_DISPLAYSWITCH_MASK_); }
    inline _ATTR_ALWAYS_INLINE_ void setDisplayBrightnessMaximum()  { setDisplayControl(DISPLAYCONTROL_DISPLAYSWITCH_ON | DISPLAYCONTROL_DIMMINGRATIO_14_16TH); }
    inline _ATTR_ALWAYS_INLINE_ void setDisplayBrightnessBrighter() { setDisplayControl(DISPLAYCONTROL_DISPLAYSWITCH_ON | DISPLAYCONTROL_DIMMINGRATIO_10_16TH); }
    inline _ATTR_ALWAYS_INLINE_ void setDisplayBrightnessDarker()   { setDisplayControl(DISPLAYCONTROL_DISPLAYSWITCH_ON | DISPLAYCONTROL_DIMMINGRATIO_04_16TH); }
    inline _ATTR_ALWAYS_INLINE_ void setDisplayBrightnessMinimum()  { setDisplayControl(DISPLAYCONTROL_DISPLAYSWITCH_ON | DISPLAYCONTROL_DIMMINGRATIO_01_16TH); }
    inline _ATTR_ALWAYS_INLINE_ void setDisplayBrightness(const unsigned int brightnessPercent) { setDisplayControl(convertBrightness(brightnessPercent)); }

    unsigned int getDisplayBrightness() const;

  protected:
    static inline _ATTR_ALWAYS_INLINE_ void setPulseWaitInterval(const unsigned int intervalMicroseconds)
    {
      if (0 == intervalMicroseconds)
        pulseWaitIntervalMicroseconds = 1; // must be greater than 0
      else
        pulseWaitIntervalMicroseconds = intervalMicroseconds;
    }

    void transferDataToAddressAutomatic(
      const uint8_t* const dataSequence,
      const size_t numberOfData,
      const uint8_t bitOrder,
      const unsigned int firstDisplayAddress
    ) const;

    void transferDataToAddressFixed(
      const uint8_t data,
      const uint8_t bitOrder,
      const unsigned int displayAddress
    ) const;

  private:
    static const uint16_t BRIGHTNESS_THRESHOLD[];
    static unsigned int pulseWaitIntervalMicroseconds;

    static uint8_t convertBrightness(const unsigned int brightnessPercent);
    static inline _ATTR_ALWAYS_INLINE_ void pulseAndWait(const uint8_t pin, const uint8_t value);

    inline _ATTR_ALWAYS_INLINE_ void commandStart() const;
    inline _ATTR_ALWAYS_INLINE_ void commandStop() const;
    void commandTransfer(const uint8_t commandOrData, const uint8_t bitOrder = LSBFIRST) const;
    inline _ATTR_ALWAYS_INLINE_ void command(const uint8_t command) const;

    void setDisplayControl(const uint8_t newDisplayControl);

    const uint8_t m_pinDIO;
    const uint8_t m_pinCLK;
    uint8_t m_displayControl = DISPLAYCONTROL_DISPLAYSWITCH_ON | DISPLAYCONTROL_DIMMINGRATIO_14_16TH;
};

#endif // TM1637Controller_h
