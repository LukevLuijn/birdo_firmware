// ======================================
// Filename:
//   Event.cpp
//
// Product or product-subsystem:
//   Statemachine template
//
// Original author:
//   Luke van Luijn (Bout Electronics)
//
// Description:
//   Event for statemachine.
// ======================================


#include "Event.h"

namespace StateMachine
{
    Event::Event(uint16_t id, uint16_t previousState) : m_id(id), m_previousState(previousState)
    {
    }
    Event& Event::operator=(const Event& anEvent)
    {
        if(this != &anEvent) {
            m_id = anEvent.m_id;
            m_previousState = anEvent.m_previousState;
        }
        return *this;
    }
    uint16_t Event::GetId() const
    {
        return m_id;
    }
    uint16_t Event::GetPreviousState() const
    {
        return m_previousState;
    }
}