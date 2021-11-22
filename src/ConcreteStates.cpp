
#include "ConcreteStates.h"
#include "BMisc.h"

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
        Utils::BMisc::println(TAG, "Init");
        m_timer = millis();
    }
    void Init::DoActivity()
    {
        if (m_app.button.IsPressed())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_PRESS),
                                      static_cast<uint16_t>(States_e::STATE_INIT));
            m_app.ScheduleEvent(event);
        }
        if (Utils::BMisc::Timer(m_timer, m_interval))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_INIT));
            m_app.ScheduleEvent(event);
        }
    }
    void Init::ExitAction() {}

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
        Utils::BMisc::println(TAG, "idle");
        m_timer = millis();
    }
    void Idle::DoActivity()
    {
        if (m_app.button.IsPressed())
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::BUTTON_PRESS),
                                      static_cast<uint16_t>(States_e::STATE_IDLE));
            m_app.ScheduleEvent(event);
        }
        if (Utils::BMisc::Timer(m_timer, m_interval))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_IDLE));
            m_app.ScheduleEvent(event);
        }
    }
    void Idle::ExitAction() {}

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
        Utils::BMisc::println(TAG, "pressed");
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
    void Pressed::ExitAction() {}

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
        Utils::BMisc::println(TAG, "pressedLong");
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
    void PressedLong::ExitAction() {}

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
        Utils::BMisc::println(TAG, "checkPress");
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

        if (Utils::BMisc::Timer(m_timer, m_interval))
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
    }
    void CheckPress::ExitAction() {}

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
        Utils::BMisc::println(TAG, "sleep");
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
    void Sleep::ExitAction() {}

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
        Utils::BMisc::println(TAG, "Message");
        m_timer = millis();
    }
    void Message::DoActivity()
    {
        if (Utils::BMisc::Timer(m_timer, m_interval))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_MESSAGE));
            m_app.ScheduleEvent(event);
        }
    }
    void Message::ExitAction() {}

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
        Utils::BMisc::println(TAG, "welldone");
        m_timer = millis();
    }
    void WellDone::DoActivity()
    {
        if (Utils::BMisc::Timer(m_timer, m_interval))
        {
            StateMachine::Event event(static_cast<uint16_t>(Events_e::TIMER_EXPIRED),
                                      static_cast<uint16_t>(States_e::STATE_WELL_DONE));
            m_app.ScheduleEvent(event);
        }
    }
    void WellDone::ExitAction() {}
}