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
#include "BDPlayer.h"

namespace Application
{
    class App : public StateMachine::Context
    {
    public:
        App();
        ~App() = default;

        void Start();
        void Loop();
        void Sound(Drivers::Sounds_e sound);

    public:
        Drivers::BDStepper stepperBot;
        Drivers::BDStepper stepperTop;
        Drivers::BDPixel pixels;
        Drivers::BDPixel nose;
        Drivers::BDButton button;
        Drivers::BDPwmLed led;
        Drivers::BDPlayer player;
    };
}

#endif // BIRDO_APP_H