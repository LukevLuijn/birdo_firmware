
#include "BDButton.h"
#include "BMisc.h"

namespace Drivers
{
    BDButton::BDButton(uint8_t pin,
                     void(pressedCallback)(void),
                     void(pressLongCallback)(void),
                     void(releasedCallback)(void),
                     void(pressDoubleCallback)(void),
                     bool inverted)
        : m_debounceTime(20),
          m_longPressTime(2000),
          m_currentHoldTime(0),
          m_lastPressType(0),
          m_isActive(false),
          m_pin(pin),
          m_lastDebounceTime(0),
          m_lastPressTime(0),
          m_lastFlickerState(0),
          m_lastSteadyState(0),
          m_prevSteadyState(0),
          m_isInverted(inverted),
          m_lastReleaseTime(0),
          m_doublePressTime(400),
          m_isPressDouble(false),
          m_pressedCallback(pressedCallback),
          m_pressLongCallback(pressLongCallback),
          m_releasedCallback(releasedCallback),
          m_pressDoubleCallback(pressDoubleCallback)
    {
    }
    void BDButton::Start()
    {
        pinMode(m_pin, INPUT_PULLUP);

        m_prevSteadyState = digitalRead(m_pin);
        m_lastSteadyState = m_prevSteadyState;
        m_lastFlickerState = m_prevSteadyState;

        m_isActive = true;
    }
    void BDButton::Pause(bool isPaused)
    {
        m_isActive = !isPaused;
    }
    void BDButton::Loop()
    {
        if (!m_isActive)
            return;

        m_isPressDouble = false;
        uint8_t currentState = digitalRead(m_pin);
        uint32_t currentTime = millis();

        if (m_lastPressType == static_cast<uint8_t>(ButtonState_e::PRESS_NORMAL) && m_currentHoldTime >= m_longPressTime)
            m_lastPressType = static_cast<uint8_t>(ButtonState_e::PRESS_LONG);

        m_currentHoldTime = (m_lastPressTime != 0) ? currentTime - m_lastPressTime : 0;

        if (currentState != m_lastFlickerState)
        {
            m_lastDebounceTime = currentTime;
            m_lastFlickerState = currentState;
        }
        if ((currentTime - m_lastDebounceTime) >= m_debounceTime)
        {
            m_prevSteadyState = m_lastSteadyState;
            m_lastSteadyState = currentState;
        }
        if (IsPressed())
        {
            m_lastPressType = static_cast<uint8_t>(ButtonState_e::PRESS_NORMAL);
            m_lastPressTime = currentTime;

            if (m_pressedCallback != nullptr)
            {
                m_pressedCallback();
            }
        }
        if (IsReleased())
        {
            m_lastPressTime = 0;

            m_isPressDouble = (millis() - m_lastReleaseTime < m_doublePressTime);
            m_lastReleaseTime = millis();

            if (m_releasedCallback != nullptr)
            {
                m_releasedCallback();
            }
        }
        if (IsPressedLong())
        {
            if (m_pressLongCallback != nullptr)
            {
                m_pressLongCallback();
            }
        }
    }
    bool BDButton::IsPressed()
    {
        if (m_isInverted)
        {
            return (m_prevSteadyState == LOW) &&
                   (m_lastSteadyState == HIGH);
        }

        return (m_prevSteadyState == HIGH) &&
               (m_lastSteadyState == LOW);
    }
    bool BDButton::IsPressedLong()
    {
        return (m_lastPressType == static_cast<uint8_t>(ButtonState_e::PRESS_NORMAL)) &&
               (m_currentHoldTime >= m_longPressTime);
    }
    bool BDButton::IsPressedDouble()
    {
        return m_isPressDouble;
    }
    bool BDButton::IsReleased()
    {
        if (m_isInverted)
        {
            return (m_prevSteadyState == HIGH) &&
                   (m_lastSteadyState == LOW);
        }

        return (m_prevSteadyState == LOW) &&
               (m_lastSteadyState == HIGH);
    }
    void BDButton::SetDebounceTime(uint32_t time)
    {
        m_debounceTime = time;
    }
    void BDButton::SetLongPressTime(uint32_t time)
    {
        m_longPressTime = time;
    }
    void BDButton::SetDoublePressTime(uint32_t time)
    {
        m_doublePressTime = time;
    }
    void BDButton::SetInverted(bool inverted)
    {
        m_isInverted = inverted;
    }
    uint32_t BDButton::GetHoldTime()
    {
        return m_currentHoldTime;
    }
    void BDButton::SetPressedCallback(void(func)(void))
    {
        m_pressedCallback = func;
    }
    void BDButton::SetReleasedCallback(void(func)(void))
    {
        m_releasedCallback = func;
    }
    void BDButton::SetPressLongCallback(void(func)(void))
    {
        m_pressLongCallback = func;
    }
    void BDButton::SetPressDoubleCallback(void(func)(void))
    {
        m_pressDoubleCallback = func;
    }
    ButtonState_e BDButton::GetLastButtonState()
    {
        return static_cast<ButtonState_e>(m_lastPressType);
    }
    bool BDButton::GetIsDoublePressed()
    {
        return m_isPressDouble;
    }
}
