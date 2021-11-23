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


#ifndef STATE_MACHINE_CONTEXT_H
#define STATE_MACHINE_CONTEXT_H

#include <memory>
#include <queue>

#include "Event.h"
#include "State.h"

namespace StateMachine
{
    class Context
    {
    public:
        Context() = default;
        Context(const Context& context) = delete;
        virtual ~Context() = default;

        void ScheduleEvent(const Event& anEvent);
        const std::shared_ptr<State>& GetCurrentState() const;
        void SetCurrentState(const std::shared_ptr<State>& newState);
        void HandleEventList();

    private:
        std::shared_ptr<State> currentState;
        std::queue<Event> events;
    };
}

#endif//STATE_MACHINE_CONTEXT_H
