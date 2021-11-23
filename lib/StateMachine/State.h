//
// Created by luke on 22-11-21.
//

#ifndef STATE_MACHINE_STATE_H
#define STATE_MACHINE_STATE_H

#include "Event.h"

namespace StateMachine {
class Context;

class State {
public:
  State() = default;
  State(const State &state) = delete;
  virtual ~State() = default;

  virtual bool HandleEvent(const Event &event, Context &context) = 0;
  virtual void EntryAction() = 0;
  virtual void DoActivity() = 0;
  virtual void ExitAction() = 0;
};
} // namespace StateMachine

#endif // STATE_MACHINE_STATE_H
