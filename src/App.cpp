// ======================================
// Filename:
//   App.cpp
//
// Product or product-subsystem:
//   application
//
// Description:
//   Main application.
// ======================================

#include "App.h"
#include "ConcreteStates.h"

namespace Application
{
    App::App()
        : Context(),
          stepperBot(Drivers::BDStepper(MOT_0_STEP_PIN, MOT_0_DIR_PIN, MOT_0_ENB_PIN, MICROSTEPS, REDUCTION)),
          stepperTop(Drivers::BDStepper(MOT_1_STEP_PIN, MOT_1_DIR_PIN, MOT_1_ENB_PIN, MICROSTEPS, REDUCTION)),
          pixels(Drivers::BDPixel(PIXEL_PIN, NUM_PIXELS, LDR_PIN)),
          nose(Drivers::BDPixel(NOSE_PIXEL_PIN, NUM_NOSE_PIXELS, LDR_PIN)),
          button(Drivers::BDButton(BUTTON_PIN)),
          led(Drivers::BDPwmLed(LED_BUT_PIN, LED_BUT_CHANNEL, LDR_PIN))
    {
    }
    void App::Start()
    {
        Drivers::BDLDR::Start(LDR_PIN);

        stepperBot.Start();
        stepperTop.Start();

        pixels.Start();
        pixels.SetBreatheTime(BASE_BREATHE_TIME);
        pixels.SetColor(DEFAULT_COLOR);

        nose.Start();
        nose.SetBreatheTime(BASE_BREATHE_TIME);
        nose.SetColor(DEFAULT_COLOR);

        led.Start();
        led.SetBreatheTime(BASE_BREATHE_TIME);

        button.Start();
        button.SetLongPressTime(BASE_LONG_PRESS_TIME);
        button.SetDoublePressTime(STATE_CHECK_PRESS_TIMER);

        auto start = std::make_shared<Init>(*this);
        SetCurrentState(start);
    }
    void App::Loop()
    {
        Drivers::BDLDR::Loop();

        stepperBot.Loop();
        stepperTop.Loop();
        pixels.Loop();
        nose.Loop();
        button.Loop();
        led.Loop();

        HandleEventList();
    }
}