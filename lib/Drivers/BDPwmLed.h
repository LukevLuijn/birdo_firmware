#ifndef BIRDO_BD_PWM_LED_H
#define BIRDO_BD_PWM_LED_H

#include <Arduino.h>

namespace Drivers
{
    enum class LedState_e : uint8_t;

    class BDPwmLed
    {
    public:
        BDPwmLed(uint8_t ledPin, uint8_t pwmChannel, uint8_t ldrPin);
        ~BDPwmLed() = default;

        void Start();
        void Loop();
        void TurnOn();
        void TurnOff();
        void Breathe();
        void SetBreatheTime(uint32_t time);

    private:
        void WriteBrightness();
        void WriteMaxBrightness();

    private:
        uint8_t m_pin;
        uint8_t m_pwmChannel;
        uint8_t m_ldrPin;
        uint8_t m_maxBrightness;
        uint8_t m_currentBrightness;
        uint32_t m_breatheTime;
        uint32_t m_breatheTimer;
        uint32_t m_breatheInterval;
        uint32_t m_sensorTimer;
        uint32_t m_sensorInterval;
        uint32_t m_updateTimer;
        uint32_t m_updateInterval;
        bool m_breatheOut;
        LedState_e m_currentState;
    };

    enum class LedState_e : uint8_t
    {
        STATE_OFF = 0,
        STATE_ON = 1,
        STATE_BREATHE = 2,
    };
}

#endif // BIRDO_BD_PWM_LED_H