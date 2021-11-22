
#include "BPwmLed.h"

#include "BLDR.h"
#include "BMisc.h"
#include "config.h"

namespace Drivers
{
    namespace
    {
        static constexpr uint16_t PWM_FREQUENCY = 5000;
        static constexpr uint16_t PWM_RESOLUTION = 8;
    }

    BPwmLed::BPwmLed(uint8_t ledPin, uint8_t pwmChannel, uint8_t ldrPin)
        : m_pin(ledPin),
          m_pwmChannel(pwmChannel),
          m_ldrPin(ldrPin),
          m_maxBrightness(255),
          m_currentBrightness(0),
          m_breatheTime(0),
          m_breatheTimer(0),
          m_breatheInterval(0),
          m_sensorTimer(0),
          m_sensorInterval(10),
          m_updateTimer(0),
          m_updateInterval(10),
          m_breatheOut(false),
          m_currentState(static_cast<LedState_e>(0))
    {
    }
    void BPwmLed::Start()
    {
        ledcSetup(m_pwmChannel, PWM_FREQUENCY, PWM_RESOLUTION);
        ledcAttachPin(m_pin, m_pwmChannel);
    }
    void BPwmLed::Loop()
    {
        if (Utils::BMisc::Timer(m_sensorTimer, m_sensorInterval))
        {
            WriteMaxBrightness();
        }

        if (m_currentState == LedState_e::STATE_ON)
        {
            m_currentBrightness = m_maxBrightness;
        }
        else if (m_currentState == LedState_e::STATE_BREATHE)
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
            }
        }

        if (Utils::BMisc::Timer(m_updateTimer, m_updateInterval))
        {
            WriteBrightness();
        }
    }
    void BPwmLed::TurnOn()
    {
        m_currentState = LedState_e::STATE_ON;

        m_breatheOut = false;
        m_currentBrightness = m_maxBrightness;
        WriteBrightness();
    }
    void BPwmLed::TurnOff()
    {
        m_currentState = LedState_e::STATE_OFF;

        m_breatheOut = true;
        m_currentBrightness = 0;
        WriteBrightness();
    }
    void BPwmLed::Breathe()
    {
        m_currentState = LedState_e::STATE_BREATHE;

        m_breatheTimer = millis();
    }
    void BPwmLed::SetBreatheTime(uint32_t time)
    {
        m_breatheTime = time;
        m_breatheInterval = m_breatheTime / m_maxBrightness;
    }
    void BPwmLed::WriteBrightness()
    {
        ledcWrite(m_pwmChannel, m_currentBrightness);
    }
    void BPwmLed::WriteMaxBrightness()
    {
        uint16_t reading = BLDR::GetReading();

        m_maxBrightness = map(reading, 0, 4095, 0, 255);
        m_maxBrightness = std::max(static_cast<uint8_t>(1), m_maxBrightness);

        if (m_currentState == LedState_e::STATE_BREATHE)
        {
            SetBreatheTime(m_breatheTime);
        }
    }
}