// ======================================
// Filename:
//   Context.cpp
//
// Product or product-subsystem:
//   Statemachine template
//
// Original author:
//   Luke van Luijn (Bout Electronics)
//
// Description:
//   Context for statemachine.
// ======================================

#include "Context.h"

namespace StateMachine
{
    const std::shared_ptr<State>& Context::GetCurrentState() const
    {
        return currentState;
    }
    void Context::SetCurrentState(const std::shared_ptr<State>& newState)
    {
        if (currentState)
        {
            currentState->ExitAction();
        }
        currentState = newState;
        currentState->EntryAction();
    }
    void Context::ScheduleEvent(const Event& anEvent)
    {
        events.push(anEvent);
    }
    void Context::HandleEventList()
    {
        if (!events.empty())
        {
            Event e = events.front();
            events.pop();
            currentState->HandleEvent(e, *this);
        }

        currentState->DoActivity();
    }
}