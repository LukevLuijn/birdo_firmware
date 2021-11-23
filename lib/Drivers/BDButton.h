
#ifndef BIRDO_BDBUTTON_H
#define BIRDO_BDBUTTON_H

#include <Arduino.h>

namespace Drivers
{
    enum class ButtonState_e : uint8_t;

    class BDButton
    {
    public:
        BDButton(uint8_t pin,
                void(pressedCallback)(void) = nullptr,
                void(pressLongCallback)(void) = nullptr,
                void(releasedCallback)(void) = nullptr,
                void(pressDoubleCallback)(void) = nullptr,
                bool inverted = false);
        ~BDButton() = default;

        void Start();
        void Pause(bool isPaused);
        void Loop();
        bool IsPressed();
        bool IsPressedLong();
        bool IsPressedDouble();
        bool IsReleased();
        void SetDebounceTime(uint32_t time);
        void SetLongPressTime(uint32_t time);
        void SetDoublePressTime(uint32_t time);
        void SetInverted(bool inverted);
        uint32_t GetHoldTime();

        void SetPressedCallback(void(func)(void));
        void SetReleasedCallback(void(func)(void));
        void SetPressLongCallback(void(func)(void));
        void SetPressDoubleCallback(void(func)(void));

        ButtonState_e GetLastButtonState();
        bool GetIsDoublePressed();

    protected:
        uint32_t m_debounceTime;
        uint32_t m_longPressTime;
        uint32_t m_currentHoldTime;
        uint8_t m_lastPressType;
        bool m_isActive;

    private:
        uint8_t m_pin;
        uint32_t m_lastDebounceTime;
        uint32_t m_lastPressTime;
        uint32_t m_lastFlickerState;
        uint32_t m_lastSteadyState;
        uint32_t m_prevSteadyState;
        bool m_isInverted;

        uint32_t m_lastReleaseTime;
        uint32_t m_doublePressTime;
        bool m_isPressDouble;

        void (*m_pressedCallback)(void);
        void (*m_pressLongCallback)(void);
        void (*m_releasedCallback)(void);
        void (*m_pressDoubleCallback)(void);
    };

    enum class ButtonState_e : uint8_t
    {
        RELEASED = 0,
        PRESS_NORMAL = 1,
        PRESS_LONG = 2,
        PRESS_DUBBLE = 3,
    };

}

#endif //BDBUTTON_H