
#include "BPixel.h"
#include "BMisc.h"
#include "BLDR.h"
#include "config.h"

#include <algorithm>

namespace Drivers
{
    BPixel::BPixel(uint8_t pin, uint8_t num_pixels, uint8_t ldrPin)
        : m_pin(pin),
          m_ldrPin(ldrPin),
          m_numPixels(num_pixels),
          m_currentBrightness(0),
          m_maxBrightness(255),
          m_breatheTime(0),
          m_breatheTimer(0),
          m_breatheInterval(0),
          m_sensorTimer(0),
          m_sensorInterval(10),
          m_updateTimer(0),
          m_updateInterval(10),
          m_breatheOut(false),
          m_currentState(static_cast<PixelState_e>(0)),
          m_pixels(Adafruit_NeoPixel(num_pixels, pin, NEO_GRB + NEO_KHZ800)),
          m_currentColor(Color{255, 255, 255})
    {
    }
    void BPixel::Start()
    {
        m_pixels.begin();
        m_pixels.clear();
        m_pixels.show();
    }
    void BPixel::Loop()
    {
        if (Utils::BMisc::Timer(m_sensorTimer, m_sensorInterval))
        {
            WriteMaxBrightness();
        }

        if (m_currentState == PixelState_e::STATE_ON)
        {
            m_pixels.setBrightness(m_maxBrightness);
        }
        else if (m_currentState == PixelState_e::STATE_BREATHE)
        {
            if (Utils::BMisc::Timer(m_breatheTimer, m_breatheInterval))
            {
                m_currentBrightness += (m_breatheOut) ? 1 : -1;

                if (m_currentBrightness >= m_maxBrightness - 1 && m_breatheOut)
                {
                    m_breatheOut = false;
                }
                else if (m_currentBrightness <= std::numeric_limits<uint8_t>::min() + 1 && !m_breatheOut)
                {
                    m_breatheOut = true;
                }

                m_pixels.setBrightness(m_currentBrightness);
                WriteColor();
            }
        }

        if (Utils::BMisc::Timer(m_updateTimer, m_updateInterval))
        {
            m_pixels.show();
        }
    }
    void BPixel::TurnOn(bool isStateChange)
    {
        if (isStateChange)
        {
            m_currentState = PixelState_e::STATE_ON;
        }
        m_breatheOut = false;
        WriteColor();
    }
    void BPixel::TurnOff(bool isStateChange)
    {
        if (isStateChange)
        {
            m_currentState = PixelState_e::STATE_OFF;
        }

        m_breatheOut = true;
        m_pixels.clear();
    }
    void BPixel::Breathe()
    {
        m_currentBrightness = m_pixels.getBrightness();
        m_currentState = PixelState_e::STATE_BREATHE;
        m_breatheTimer = millis();
    }
    void BPixel::SetColor(const Color &color)
    {
        m_currentColor = color;

        if (m_currentState == PixelState_e::STATE_ON)
        {
            TurnOn(false);
        }
    }
    void BPixel::SetColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        m_currentColor = {red, green, blue};

        if (m_currentState == PixelState_e::STATE_ON)
        {
            TurnOn(false);
        }
    }
    void BPixel::SetBreatheTime(uint32_t time)
    {
        m_breatheTime = time;
        m_breatheInterval = m_breatheTime / m_maxBrightness;
    }
    uint32_t BPixel::ConvertColor(const Color &color)
    {
        return m_pixels.Color(color.R, color.G, color.B);
    }
    void BPixel::WriteColor()
    {
        for (uint8_t i = 0; i < m_numPixels; ++i)
        {
            m_pixels.setPixelColor(i, ConvertColor(m_currentColor));
        }
    }
    void BPixel::WriteMaxBrightness()
    {
        uint16_t reading = BLDR::GetReading();

        m_maxBrightness = map(reading, 0, 4095, 0, 255);
        m_maxBrightness = std::max(static_cast<uint8_t>(1), m_maxBrightness);

        if (m_currentState == PixelState_e::STATE_BREATHE)
        {
            SetBreatheTime(m_breatheTime);
        }
    }

}