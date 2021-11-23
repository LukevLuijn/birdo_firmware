// ======================================
// Filename:
//   BDPixel.h
//
// Product or product-subsystem:
//   Hardware drivers
//
// Original author:
//   Luke van Luijn (Bout Electronics)
//
// Description:
//   Driver for Adafruit NeoPixel strip.
// ======================================

#ifndef BIRDO_BDPIXEL_H
#define BIRDO_BDPIXEL_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "BDLDR.h"

namespace Drivers
{
    enum class PixelState_e : uint8_t;
    
    struct Color
    {
        uint8_t R,G,B;
    };

    class BDPixel
    {
    public:
        BDPixel(uint8_t pin, uint8_t num_pixels, uint8_t ldrPin);
        ~BDPixel() = default;

        void Start();
        void Loop();
        void TurnOn(bool isStateChange = true);
        void TurnOff(bool isStateChange = true);
        void Breathe();
        void SetColor(const Color &color);
        void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        void SetBreatheTime(uint32_t time);

    private:
        uint32_t ConvertColor(const Color& color);
        void WriteColor();
        void WriteMaxBrightness();

    private:
        uint8_t m_pin;
        uint8_t m_ldrPin;
        uint8_t m_numPixels;
        uint8_t m_currentBrightness;
        uint8_t m_maxBrightness;
        
        uint32_t m_breatheTime;
        uint32_t m_breatheTimer;
        uint32_t m_breatheInterval;

        uint32_t m_sensorTimer;
        uint32_t m_sensorInterval;

        uint32_t m_updateTimer;
        uint32_t m_updateInterval;

        bool m_breatheOut;

        PixelState_e m_currentState;
        Adafruit_NeoPixel m_pixels;
        Color m_currentColor;
    };

    enum class PixelState_e : uint8_t
    {
        STATE_OFF = 0,
        STATE_ON = 1,
        STATE_BREATHE = 2,
    };
}

#endif // BIRDO_BDPIXEL_H