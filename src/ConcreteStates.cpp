// ======================================
// Filename:
//   ConcreteStates.cpp
//
// Product or product-subsystem:
//   application
//
// Description:
//   Actual states for statemachine.
// ======================================

#include "ConcreteStates.h"
#include "Misc.h"

namespace Application
{
    namespace
    {
        const char *TAG = "STATE";
    }

    // ================ Init =================================== //
    bool Init::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::BUTTON_PRESS:
        {
            auto state = std::make_shared<Pressed>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::TIMER_EXPIRED:
        {
            auto state = std::make_shared<Idle>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::BUTTON_PRESS_LONG:
        case Events_e::BUTTON_PRESS_DOUBLE:
        case Events_e::BUTTON_RELEASED:
        case Events_e::EVENT_PRESS_LONG:
        case Events_e::EVENT_PRESS_NORMAL:
        default:
            return false;
        }
    }
    void Init::EntryAction()
    {
        Utils::Misc::println(TAG, "Init");
        m_timer = millis();

        m_app.nose.TurnOff();
        m_app.pixels.TurnOff();

        uint16_t rotation = 270;
        m_app.stepperBot.MoveDegrees(rotation);
        m_app.stepperTop.MoveDegrees(-rotation);

        m_app.pixels.SetColor(ACCENT_COLOR);
        m_app.nose.SetColor(ACCENT_COLOR);

        m_app.pixels.TurnOn();
        m_app.nose.TurnOn();

        m_previousMotorSpeed = std::max(m_app.stepperBot.maxSpeed(), m_app.stepperTop.maxSpeed());
    }
    void Init::DoActivity()
    {
        if (m_app.button.IsPressed())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_PRESS),
                                      static_cast<uint16_t>(States_e::STATE_INIT));
            m_app.ScheduleEvent(event);
        }
        if (Utils::Misc::Timer(m_timer, STATE_INIT_TIMER))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_INIT));
            m_app.ScheduleEvent(event);
        }

        if (!m_movementComplete &&
            m_app.stepperBot.distanceToGo() == 0 &&
            m_app.stepperTop.distanceToGo() == 0)
        {
            m_app.stepperBot.setMaxSpeed(m_previousMotorSpeed / 5);
            m_app.stepperTop.setMaxSpeed(m_previousMotorSpeed / 5);

            m_app.stepperBot.MoveTo(0);
            m_app.stepperTop.MoveTo(0);

            m_app.pixels.TurnOff();
            m_app.nose.TurnOff();
            m_app.pixels.SetColor(DEFAULT_COLOR);
            m_app.nose.SetColor(DEFAULT_COLOR);

            uint32_t time = m_timer + STATE_INIT_TIMER - millis();
            m_app.nose.SetBreatheTime(time);
            m_app.pixels.SetBreatheTime(time);

            m_app.nose.Breathe();
            m_app.pixels.Breathe();

            m_movementComplete = true;
        }
    }
    void Init::ExitAction()
    {
        m_app.stepperBot.setMaxSpeed(m_previousMotorSpeed);
        m_app.stepperTop.setMaxSpeed(m_previousMotorSpeed);

        m_app.stepperBot.MoveTo(0);
        m_app.stepperTop.MoveTo(0);

        m_app.nose.TurnOn();
        m_app.pixels.TurnOn();
    }

    // ================ IDLE ==================================== //
    bool Idle::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::BUTTON_PRESS:
        {
            auto state = std::make_shared<Pressed>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::TIMER_EXPIRED:
        {
            auto state = std::make_shared<Idle>(m_app);
            context.SetCurrentState(state);

            // Transition
            uint16_t min = 180, max = 360;
            int32_t position = Utils::Misc::Random(min, max);
            m_app.stepperBot.MoveDegrees(position);
            m_app.stepperTop.MoveDegrees(-position);

            return true;
        }
        case Events_e::BUTTON_PRESS_LONG:
        case Events_e::BUTTON_PRESS_DOUBLE:
        case Events_e::BUTTON_RELEASED:
        case Events_e::EVENT_PRESS_LONG:
        case Events_e::EVENT_PRESS_NORMAL:
        default:
            return false;
        }
    }
    void Idle::EntryAction()
    {
        Utils::Misc::println(TAG, "idle");
        m_timer = millis();
    }
    void Idle::DoActivity()
    {
        if (m_app.button.IsPressed())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_PRESS),
                                      static_cast<uint16_t>(States_e::STATE_IDLE));
            m_app.ScheduleEvent(event);

            m_app.stepperBot.MoveTo(0);
            m_app.stepperTop.MoveTo(0);
        }
        if (Utils::Misc::Timer(m_timer, STATE_IDLE_TIMER))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_IDLE));
            m_app.ScheduleEvent(event);
        }

        if (!m_transitionComplete &&
            m_app.stepperBot.distanceToGo() == 0 &&
            m_app.stepperTop.distanceToGo() == 0)
        {
            m_app.stepperBot.MoveTo(0);
            m_app.stepperTop.MoveTo(0);
            m_transitionComplete = true;
        }
    }
    void Idle::ExitAction()
    {
        // nothing yet.
    }

    // ================ PRESSED ================================= //
    bool Pressed::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::BUTTON_PRESS_LONG:
        {
            auto state = std::make_shared<PressedLong>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::BUTTON_RELEASED:
        {
            auto state = std::make_shared<CheckPress>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::BUTTON_PRESS:
        case Events_e::TIMER_EXPIRED:
        case Events_e::BUTTON_PRESS_DOUBLE:
        case Events_e::EVENT_PRESS_LONG:
        case Events_e::EVENT_PRESS_NORMAL:
        default:
            return false;
        }
    }
    void Pressed::EntryAction()
    {
        Utils::Misc::println(TAG, "pressed");
        m_app.nose.SetColor(ACCENT_COLOR);
        m_app.nose.TurnOn();
    }
    void Pressed::DoActivity()
    {
        if (m_app.button.IsPressedLong())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_PRESS_LONG),
                                      static_cast<uint16_t>(States_e::STATE_PRESSED));
            m_app.ScheduleEvent(event);
        }
        if (m_app.button.IsReleased())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_RELEASED),
                                      static_cast<uint16_t>(States_e::STATE_PRESSED));
            m_app.ScheduleEvent(event);
        }
    }
    void Pressed::ExitAction()
    {
        // m_app.nose.SetColor(DEFAULT_COLOR);
        // m_app.nose.TurnOn();
    }

    // ================ PRESSED_LONG ============================ //
    bool PressedLong::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::BUTTON_RELEASED:
        {
            auto state = std::make_shared<CheckPress>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::TIMER_EXPIRED:
        case Events_e::BUTTON_PRESS_LONG:
        case Events_e::BUTTON_PRESS_DOUBLE:
        case Events_e::BUTTON_PRESS:
        case Events_e::EVENT_PRESS_LONG:
        case Events_e::EVENT_PRESS_NORMAL:
        default:
            return false;
        }
    }
    void PressedLong::EntryAction()
    {
        Utils::Misc::println(TAG, "pressedLong");

        m_app.nose.SetColor(ACCENT_COLOR);
        m_app.nose.SetBreatheTime(BASE_BREATHE_TIME);
        m_app.nose.Breathe();
    }
    void PressedLong::DoActivity()
    {
        if (m_app.button.IsReleased())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_RELEASED),
                                      static_cast<uint16_t>(States_e::STATE_PRESSED_LONG));
            m_app.ScheduleEvent(event);
        }
    }
    void PressedLong::ExitAction()
    {
        // m_app.nose.SetColor(DEFAULT_COLOR);
        // m_app.nose.TurnOn();
    }

    // ================ CHECK_PRESS ============================ //
    bool CheckPress::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::BUTTON_PRESS:
        {
            auto state = std::make_shared<Pressed>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::BUTTON_PRESS_DOUBLE:
        {
            auto state = std::make_shared<Sleep>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::EVENT_PRESS_NORMAL:
        {
            auto state = std::make_shared<WellDone>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::EVENT_PRESS_LONG:
        {
            auto state = std::make_shared<Message>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::TIMER_EXPIRED:
        case Events_e::BUTTON_PRESS_LONG:
        case Events_e::BUTTON_RELEASED:
        default:
            return false;
        }
    }
    void CheckPress::EntryAction()
    {
        Utils::Misc::println(TAG, "checkPress");
        m_timer = millis();
    }
    void CheckPress::DoActivity()
    {
        if (m_app.button.IsPressedDouble())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_PRESS_DOUBLE),
                                      static_cast<uint16_t>(States_e::STATE_CHECK_PRESS));
            m_app.ScheduleEvent(event);
        }

        if (Utils::Misc::Timer(m_timer, STATE_CHECK_PRESS_TIMER))
        {
            if (m_app.button.GetLastButtonState() == Drivers::ButtonState_e::PRESS_NORMAL)
            {
                StateMachine::Event event(static_cast<uint16_t>(Events_e::EVENT_PRESS_NORMAL),
                                          static_cast<uint16_t>(States_e::STATE_CHECK_PRESS));
                m_app.ScheduleEvent(event);
            }
            else if (m_app.button.GetLastButtonState() == Drivers::ButtonState_e::PRESS_LONG)
            {
                StateMachine::Event event(static_cast<uint16_t>(Events_e::EVENT_PRESS_LONG),
                                          static_cast<uint16_t>(States_e::STATE_CHECK_PRESS));
                m_app.ScheduleEvent(event);
            }
        }

        if (m_app.button.IsPressed())
        {
            m_app.nose.SetColor(ACCENT_COLOR);
            m_app.nose.TurnOn();
        }
        if (m_app.button.IsPressedLong())
        {
            m_app.nose.SetColor(ACCENT_COLOR);
            m_app.nose.SetBreatheTime(BASE_BREATHE_TIME);
            m_app.nose.Breathe();
        }
    }
    void CheckPress::ExitAction()
    {
        m_app.nose.SetColor(DEFAULT_COLOR);
        m_app.nose.TurnOn();
    }

    // ================ SLEEP =================================== //
    bool Sleep::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::BUTTON_PRESS:
        {
            auto state = std::make_shared<Init>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::BUTTON_PRESS_DOUBLE:
        case Events_e::TIMER_EXPIRED:
        case Events_e::BUTTON_PRESS_LONG:
        case Events_e::BUTTON_RELEASED:
        case Events_e::EVENT_PRESS_LONG:
        case Events_e::EVENT_PRESS_NORMAL:
        default:
            return false;
        }
    }
    void Sleep::EntryAction()
    {
        Utils::Misc::println(TAG, "sleep");
        m_app.nose.TurnOff();
        m_app.pixels.TurnOff();
    }
    void Sleep::DoActivity()
    {
        if (m_app.button.IsPressed())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_PRESS),
                                      static_cast<uint16_t>(States_e::STATE_SLEEP));
            m_app.ScheduleEvent(event);
        }
    }
    void Sleep::ExitAction()
    {
        // nothing yet.
    }

    // ================ MESSAGE ================================= //
    bool Message::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::TIMER_EXPIRED:
        {
            auto state = std::make_shared<Idle>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::BUTTON_PRESS_DOUBLE:
        case Events_e::BUTTON_PRESS:
        case Events_e::BUTTON_PRESS_LONG:
        case Events_e::BUTTON_RELEASED:
        case Events_e::EVENT_PRESS_LONG:
        case Events_e::EVENT_PRESS_NORMAL:
        default:
            return false;
        }
    }
    void Message::EntryAction()
    {
        Utils::Misc::println(TAG, "Message");
        m_timer = millis();

        m_app.nose.SetColor(MESSAGE_COLOR);
        m_app.nose.SetBreatheTime(BASE_BREATHE_TIME);
        m_app.nose.Breathe();

        uint16_t rotation = 135;
        m_app.stepperBot.MoveDegrees(rotation);
        m_app.stepperTop.MoveDegrees(-rotation);
    }
    void Message::DoActivity()
    {
        if (m_app.stepperBot.distanceToGo() == 0 && m_app.stepperTop.distanceToGo() == 0)
        {
            m_app.stepperBot.MoveTo(-m_app.stepperBot.currentPosition());
            m_app.stepperTop.MoveTo(-m_app.stepperTop.currentPosition());
        }

        if (Utils::Misc::Timer(m_timer, STATE_MESSAGE_TIMER))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_MESSAGE));
            m_app.ScheduleEvent(event);
        }
    }
    void Message::ExitAction()
    {
        m_app.nose.SetColor(DEFAULT_COLOR);
        m_app.nose.TurnOn();

        m_app.stepperBot.MoveTo(0);
        m_app.stepperTop.MoveTo(0);
    }

    // ================ WELL_DONE =============================== //
    bool WellDone::HandleEvent(const Event &event, Context &context)
    {
        switch (static_cast<Events_e>(event.GetId()))
        {
        case Events_e::TIMER_EXPIRED:
        {
            auto state = std::make_shared<Idle>(m_app);
            context.SetCurrentState(state);
            return true;
        }
        case Events_e::BUTTON_PRESS_DOUBLE:
        case Events_e::BUTTON_PRESS:
        case Events_e::BUTTON_PRESS_LONG:
        case Events_e::BUTTON_RELEASED:
        case Events_e::EVENT_PRESS_LONG:
        case Events_e::EVENT_PRESS_NORMAL:
        default:
            return false;
        }
    }
    void WellDone::EntryAction()
    {
        Utils::Misc::println(TAG, "welldone");
        m_timer = millis();

        m_app.nose.SetColor(WELL_DONE_COLOR);
        m_app.nose.TurnOn();

        uint16_t min = 180, max = 360;
        int32_t position = Utils::Misc::Random(min, max);
        m_app.stepperBot.MoveDegrees(position);
        m_app.stepperTop.MoveDegrees(-position);
    }
    void WellDone::DoActivity()
    {
        if (m_app.stepperBot.distanceToGo() == 0 && m_app.stepperTop.distanceToGo() == 0)
        {
            uint16_t min = 180, max = 360;
            int32_t position = (m_goBack) ? 0 : Utils::Misc::Random(min, max);
            m_app.stepperBot.MoveTo((m_goBack) ? -position : position);
            m_app.stepperTop.MoveTo((m_goBack) ? position : -position);
            m_goBack = !m_goBack;
        }
        if (Utils::Misc::Timer(m_timer, STATE_WELL_DONE_TIMER))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_WELL_DONE));
            m_app.ScheduleEvent(event);
        }
    }
    void WellDone::ExitAction()
    {
        m_app.nose.SetColor(DEFAULT_COLOR);
        m_app.nose.TurnOn();

        m_app.stepperBot.MoveTo(0);
        m_app.stepperTop.MoveTo(0);
    }
}