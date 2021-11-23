// ======================================
// Filename:
//   Misc.h
//
// Product or product-subsystem:
//   Miscellaneous methods
//
// Original author:
//   Luke van Luijn (Bout Electronics)
//
// Description:
//   Miscellaneous methods.
// ======================================

#ifndef BIRDO_MISC_H
#define BIRDO_MISC_H

#include <Arduino.h>
#include <random>

namespace Utils
{
    namespace
    {
        const bool DEBUG_MODE = true;
    }

    class Misc
    {
    public:
        static bool Timer(uint32_t &previousTime, uint32_t interval)
        {
            if (millis() - previousTime >= interval)
            {
                previousTime = millis();
                return true;
            }
            return false;
        }
        static uint32_t Random(uint32_t min, uint32_t max)
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<uint32_t> dis(min, max);
            return static_cast<uint32_t> (dis(gen));
        }
        template <typename T>
        static void print(T message)
        {
            if (DEBUG_MODE)
            {
                Serial.print(message);
            }
        }

        template <typename T>
        static void println(T message)
        {
            if (DEBUG_MODE)
            {
                Serial.println(message);
            }
        }

        template <typename T>
        static void print(const char *tag, T message)
        {
            if (DEBUG_MODE)
            {
                Serial.print("[");
                Serial.print(tag);
                Serial.print("]\t");
                Serial.print(message);
            }
        }

        template <typename T>
        static void println(const char *tag, T message)
        {
            if (DEBUG_MODE)
            {
                Serial.print("[");
                Serial.print(tag);
                Serial.print("]\t");
                Serial.println(message);
            }
        }
    };
}

#endif // BIRDO_BMISC_H