
#ifndef BIRDO_BSTEPPER_H
#define BIRDO_BSTEPPER_H

#include "Arduino.h"
#include "AccelStepper.h"

namespace Drivers
{
    enum class Microsteps_e : uint8_t;

    class BStepper : public AccelStepper
    {
    public:
        BStepper(uint8_t stepPin, uint8_t dirPin, uint8_t enbPin, Microsteps_e microsteps = static_cast<Microsteps_e>(0), float reduction = 0.0f);
        ~BStepper() = default;

        void Start();
        void Loop();
        void MoveDegrees(float degrees);

    private:
        const uint8_t MULTIPLIERS [8] = {1, 2, 4, 8, 16, 32, 64, 128};
        const uint16_t STEPS_PER_REVOLUTION = 200;
        Microsteps_e m_microsteps;
        float m_reduction;
        bool m_isEnabled;
    };

    enum class Microsteps_e : uint8_t
    {
        STEP_1_1 = 0,
        STEP_1_2 = 1,
        STEP_1_4 = 2,
        STEP_1_8 = 3,
        STEP_1_16 = 4,
        STEP_1_32 = 5,
        STEP_1_64 = 6,
        STEP_1_128 = 7,
    };
}

#endif // BIRDO_BSTEPPER_H