#ifndef BIRDO_BLDR_H
#define BIRDO_BLDR_H

#include <Arduino.h>

namespace Drivers
{
    class BLDR
    {
    public:
        static void Start(uint8_t pin);
        static void Loop();

        static uint16_t GetReading();

    private:
        static constexpr uint8_t BUFFER_SIZE = 20;
        static uint8_t m_pin;
        static uint32_t m_timer;
        static uint32_t m_interval;
        static uint8_t m_currentIndex;
        static uint8_t m_reachedIndex;
        static uint16_t m_buffer[BUFFER_SIZE];
    };
}

#endif //BIRDO_BLDR_H