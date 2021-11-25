
#ifndef BIRDO_BDPLAYER_H
#define BIRDO_BDPLAYER_H

#include <Arduino.h>

#include "DFRobotDFPlayerMini.h"

namespace Drivers
{
    enum class Sounds_e : uint8_t;

    class BDPlayer : public DFRobotDFPlayerMini
    {
    public:
        BDPlayer(uint8_t RX, uint8_t TX);
        ~BDPlayer() = default;

        void Start();
        void Play(Sounds_e sound, uint8_t volume = 10);

        bool IsFinished();

    private:
        uint8_t m_RX;
        uint8_t m_TX;

        HardwareSerial m_HS;
    };

    enum class Sounds_e : uint8_t
    {
        VINK_HAPPY = 1,
        NIGHTINGALE_WELL_DONE = 2,
        MORNING_CHICKEN = 3,
        FIET_VIEW = 4,
        COMMON_QUAIL_SOFT_TO_LOUD = 5,
        CARTOON_BIRD_HAPPY = 6,
        CARTOON_BIRD_CHIRPING = 7,
        CARTOON_BIRD = 8,
        BLACKBIRD = 9,
        BARKING_DOG = 10,
    };
}

#endif // BIRDO_BDPLAYER_H