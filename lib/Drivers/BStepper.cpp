
#include "BStepper.h"

namespace Drivers
{
    BStepper::BStepper(uint8_t stepPin, uint8_t dirPin, uint8_t enbPin, Microsteps_e microsteps, float reduction)
        : AccelStepper(1, stepPin, dirPin), m_microsteps(microsteps), m_reduction(reduction), m_isEnabled(false)
    {
        pinMode(enbPin, OUTPUT);
        setEnablePin(enbPin);
        setPinsInverted(false, false, true); // invert enable
    }
    void BStepper::Start()
    {
        uint16_t stepsPerRev = STEPS_PER_REVOLUTION * MULTIPLIERS[static_cast<uint8_t>(m_microsteps)] * m_reduction;
        setMaxSpeed(stepsPerRev);
        setAcceleration(1000);
        disableOutputs();
    }
    void BStepper::Loop()
    {
        run();

        if (distanceToGo() == 0 && m_isEnabled)
        {
            m_isEnabled = false;
            disableOutputs();
        }
    }
    void BStepper::MoveDegrees(float degrees)
    {
        uint16_t stepsPerRev = STEPS_PER_REVOLUTION * MULTIPLIERS[static_cast<uint8_t>(m_microsteps)] * m_reduction;
        float stepAngle = 360.0f / stepsPerRev;
        int64_t steps = static_cast<int64_t>(degrees / stepAngle);

        enableOutputs();
        m_isEnabled = true;
        moveTo(steps);
    }
}
