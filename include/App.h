// ======================================
// Filename:
//   App.h
//
// Product or product-subsystem:
//   application
//
// Description:
//   Main application.
// ======================================

#ifndef BIRDO_APP_H
#define BIRDO_APP_H

#include "Context.h"

#include "config.h"
#include "BDStepper.h"
#include "BDPixel.h"
#include "BDButton.h"
#include "BDPwmLed.h"
#include "BDLDR.h"

namespace Application
{
    class App : public StateMachine::Context
    {
    public:
        App();
        ~App() = default;

        void Start();
        void Loop();

    public:
        Drivers::BDStepper stepperBot;
        Drivers::BDStepper stepperTop;
        Drivers::BDPixel pixels;
        Drivers::BDButton button;
        Drivers::BDPwmLed led;
    };
}

#endif // BIRDO_APP_H