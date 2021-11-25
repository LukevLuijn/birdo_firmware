
#include "BDPlayer.h"
#include "Misc.h"

#include <algorithm>

namespace Drivers
{
    namespace 
    {
        const char * TAG = "SOUND";
        const uint16_t BAUDRATE = 9600;
        const uint8_t MAX_ATTEMPTS = 20;
        const uint8_t MAX_VOLUME = 30;
    }

    BDPlayer::BDPlayer(uint8_t RX, uint8_t TX)
        : DFRobotDFPlayerMini(), m_RX(RX), m_TX(TX), m_HS(1)
    {
    }
    void BDPlayer::Start()
    {
        m_HS.begin(BAUDRATE, SERIAL_8N1, m_RX, m_TX);

        uint8_t counter = 0;

        while (!begin(m_HS))
        {
            if (counter >= MAX_ATTEMPTS)
            {
                Utils::Misc::println(TAG, "ERROR max attempts reached, no sound");
                return;
            }

            delay(10);
            ++counter;
        }

        reset();
        EQ(DFPLAYER_EQ_NORMAL);
        outputDevice(DFPLAYER_DEVICE_SD);
    }
    void BDPlayer::Play(Sounds_e sound, uint8_t volume)
    {
        DFRobotDFPlayerMini::volume(std::min(volume, MAX_VOLUME));
        play(static_cast<int32_t>(sound));
    }
    bool BDPlayer::IsFinished()
    {
        return (readType() == DFPlayerPlayFinished);
    }
}