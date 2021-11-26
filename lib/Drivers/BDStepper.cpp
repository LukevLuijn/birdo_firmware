// ======================================
// Filename:
//   BDStepper.cpp
//
// Product or product-subsystem:
//   Hardware drivers
//
// Original author:
//   Luke van Luijn (Bout Electronics)
//
// Description:
//   Driver for stepper control.
// ======================================

#include "BDStepper.h"
#include "Misc.h"

namespace Drivers
{
    namespace
    {
        const char *TAG = "STEP";
    }

    BDStepper::BDStepper(uint8_t stepPin, uint8_t dirPin, uint8_t enbPin, Microsteps_e microsteps, float reduction)
        : AccelStepper(1, stepPin, dirPin), m_microsteps(microsteps), m_reduction(reduction), m_isEnabled(false)
    {
        pinMode(enbPin, OUTPUT);
        setEnablePin(enbPin);
        setPinsInverted(false, false, true); // invert enable
    }
    void BDStepper::Start()
    {
        setCurrentPosition(0);
        uint16_t stepsPerRev = STEPS_PER_REVOLUTION * MULTIPLIERS[static_cast<uint8_t>(m_microsteps)] * m_reduction;

        float multiplier = 1.0f;
        float speed = stepsPerRev * multiplier;

        multiplier = 0.50f;
        float accel = (1000.0f * (static_cast<float>(stepsPerRev) / 400.0f)) * multiplier;

        setMaxSpeed(speed);
        setAcceleration(accel);
        disableOutputs();

        Utils::Misc::print(TAG, "speed = ");
        Utils::Misc::print(speed);
        Utils::Misc::print(", accel = ");
        Utils::Misc::println(accel);
    }
    void BDStepper::Loop()
    {
        run();

        if (distanceToGo() == 0 && m_isEnabled)
        {
            m_isEnabled = false;
            disableOutputs();
        }
    }
    void BDStepper::MoveDegrees(float degrees)
    {
        uint16_t stepsPerRev = STEPS_PER_REVOLUTION * MULTIPLIERS[static_cast<uint8_t>(m_microsteps)] * m_reduction;
        float stepAngle = 360.0f / stepsPerRev;
        int64_t steps = static_cast<int64_t>(degrees / stepAngle);

        enableOutputs();
        m_isEnabled = true;
        moveTo(steps);
    }
    void BDStepper::MoveTo(float position)
    {
        enableOutputs();
        m_isEnabled = true;
        moveTo(position);
    }
}
