// ======================================
// Filename:
//   ConcreteStates.h
//
// Product or product-subsystem:
//   application
//
// Description:
//   Actual states for statemachine.
// ======================================

#ifndef BIRDO_CONCRETE_STATES_H
#define BIRDO_CONCRETE_STATES_H

#include "State.h"
#include "App.h"

using StateMachine::Context;
using StateMachine::Event;

namespace Application
{
    enum class States_e : uint8_t;
    enum class Events_e : uint8_t;

    class BaseState : public StateMachine::State
    {
    public:
        ~BaseState() override = default;

    protected:
        explicit BaseState(App &app) : m_app(app) {}

    protected:
        App &m_app;
    };
    class Init : public BaseState
    {
    public:
        explicit Init(App &app) : BaseState(app),
                                  m_timer(0),
                                  m_previousMotorSpeed(0),
                                  m_movementComplete(false)
        {
        }
        ~Init() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;

    private:
        uint32_t m_timer;
        uint32_t m_previousMotorSpeed;
        bool m_movementComplete;
    };
    class Idle : public BaseState
    {
    public:
        explicit Idle(App &app) : BaseState(app),
                                  m_timer(0),
                                  m_transitionComplete(false) {}
        ~Idle() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;

    private:
        void Transition();

    private:
        uint32_t m_timer;
        bool m_transitionComplete;
    };
    class Pressed : public BaseState
    {
    public:
        explicit Pressed(App &app) : BaseState(app) {}
        ~Pressed() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;
    };
    class PressedLong : public BaseState
    {
    public:
        explicit PressedLong(App &app) : BaseState(app) {}
        ~PressedLong() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;
    };
    class CheckPress : public BaseState
    {
    public:
        explicit CheckPress(App &app) : BaseState(app),
                                        m_timer(0)
        {
        }
        ~CheckPress() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;

    private:
        uint32_t m_timer;
    };
    class Sleep : public BaseState
    {
    public:
        explicit Sleep(App &app) : BaseState(app) {}
        ~Sleep() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;
    };
    class Message : public BaseState
    {
    public:
        explicit Message(App &app) : BaseState(app),
                                     m_timer(0) {}
        ~Message() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;

    private:
        uint32_t m_timer;
    };
    class WellDone : public BaseState
    {
    public:
        explicit WellDone(App &app) : BaseState(app),
                                      m_timer(0),
                                      m_goBack(true) {}
        ~WellDone() override = default;

        bool HandleEvent(const Event &event, Context &context) override;
        void EntryAction() override;
        void DoActivity() override;
        void ExitAction() override;

    private:
        uint32_t m_timer;
        bool m_goBack;
    };
    enum class Events_e : uint8_t
    {
        BUTTON_PRESS = 0,
        BUTTON_PRESS_LONG = 1,
        BUTTON_PRESS_DOUBLE = 2,
        BUTTON_RELEASED = 3,
        TIMER_EXPIRED = 4,
        EVENT_PRESS_NORMAL = 5,
        EVENT_PRESS_LONG = 6,
    };
    enum class States_e : uint8_t
    {
        STATE_INIT = 0,
        STATE_IDLE = 1,
        STATE_PRESSED = 2,
        STATE_PRESSED_LONG = 3,
        STATE_CHECK_PRESS = 4,
        STATE_SLEEP = 5,
        STATE_MESSAGE = 6,
        STATE_WELL_DONE = 7,
    };
}

#endif // BIRDO_CONCRETE_STATES_H