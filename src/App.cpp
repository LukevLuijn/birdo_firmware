
#include "App.h"
#include "ConcreteStates.h"

namespace Application
{
    App::App()
        : Context(),
          stepperBot(Drivers::BStepper(MOT_0_STEP_PIN, MOT_0_DIR_PIN, MOT_0_ENB_PIN, MICROSTEPS, REDUCTION)),
          stepperTop(Drivers::BStepper(MOT_1_STEP_PIN, MOT_1_DIR_PIN, MOT_1_ENB_PIN, MICROSTEPS, REDUCTION)),
          pixels(Drivers::BPixel(PIXEL_PIN, NUM_PIXELS, LDR_PIN)),
          button(Drivers::BButton(BUTTON_PIN)),
          led(Drivers::BPwmLed(LED_BUT_PIN, LED_BUT_CHANNEL, LDR_PIN))
    {
    }
    void App::Start()
    {
        auto start = std::make_shared<Init>(*this);
        SetCurrentState(start);

        Drivers::BLDR::Start(LDR_PIN);

        stepperBot.Start();
        stepperTop.Start();

        pixels.Start();
        pixels.SetBreatheTime(1000);

        button.Start();
        button.SetLongPressTime(1000);

        led.Start();
        led.SetBreatheTime(1000);
    }
    void App::Loop()
    {
        Drivers::BLDR::Loop();

        stepperBot.Loop();
        stepperTop.Loop();
        pixels.Loop();
        button.Loop();
        led.Loop();

        HandleEventList();
    }
}