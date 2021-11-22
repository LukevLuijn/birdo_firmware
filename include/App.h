
#ifndef BIRDO_APP_H
#define BIRDO_APP_H

#include "Context.h"

#include "config.h"
#include "BStepper.h"
#include "BPixel.h"
#include "BButton.h"
#include "BPwmLed.h"
#include "BLDR.h"

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
        Drivers::BStepper stepperBot;
        Drivers::BStepper stepperTop;
        Drivers::BPixel pixels;
        Drivers::BButton button;
        Drivers::BPwmLed led;
    };
}

#endif // BIRDO_APP_H