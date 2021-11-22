
#include "BLDR.h"

#include <algorithm>

#include "BMisc.h"

namespace Drivers
{
    namespace
    {
        static constexpr uint16_t READING_MIN = 1;
        static constexpr uint16_t READING_MAX = 4095;
    }

    /*static*/ uint8_t BLDR::m_pin = 0;
    /*static*/ uint32_t BLDR::m_timer = 0;
    /*static*/ uint32_t BLDR::m_interval = 0;
    /*static*/ uint8_t BLDR::m_currentIndex = 0;
    /*static*/ uint8_t BLDR::m_reachedIndex = 0;
    /*static*/ uint16_t BLDR::m_buffer[] = {};

    /*static*/ void BLDR::Start(uint8_t pin)
    {
        m_pin = pin;
        m_timer = millis();
        m_interval = 10;
        m_currentIndex = 0;

        for (uint8_t i = 0; i < BUFFER_SIZE; ++i)
        {
            m_buffer[i] = 0;
        }
    }
    /*static*/ void BLDR::Loop()
    {
        if (Utils::BMisc::Timer(m_timer, m_interval))
        {
            m_buffer[m_currentIndex] = analogRead(m_pin);

            ++m_currentIndex;
            m_currentIndex = (m_currentIndex < BUFFER_SIZE) ? m_currentIndex : 0;
            m_reachedIndex += (m_reachedIndex < BUFFER_SIZE) ? 1 : 0;
        }
    }
    /*static*/ uint16_t BLDR::GetReading()
    {
        uint32_t sum = 0;
        for (uint8_t i = 0; i < BUFFER_SIZE; ++i)
        {
            sum += m_buffer[i];
        }
        uint8_t nSamples = (m_reachedIndex < BUFFER_SIZE) ? m_reachedIndex : BUFFER_SIZE;
        auto average = static_cast<uint16_t>(sum / std::max(nSamples, static_cast<uint8_t>(1)));
        average = std::max(static_cast<uint16_t>(READING_MIN), average);
        average = std::min(static_cast<uint16_t>(READING_MAX), average);
        return average;
    }
}