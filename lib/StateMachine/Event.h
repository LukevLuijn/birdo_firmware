//
// Created by luke on 22-11-21.
//

#ifndef STATE_MACHINE_EVENT_H
#define STATE_MACHINE_EVENT_H

#include <cstdint>

namespace StateMachine
{
    class Event
    {
    public:
        explicit Event(uint16_t id, uint16_t previousState);
        Event(const Event &anEvent) = default;
        virtual ~Event() = default;

        Event &operator=(const Event &anEvent);
        uint16_t GetId() const;
        uint16_t GetPreviousState() const;

    private:
        uint16_t m_id;
        uint16_t m_previousState;
    };
}

#endif //STATE_MACHINE_EVENT_H
