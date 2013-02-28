#pragma once
#include <memory>

namespace ProjectR
{
class IState;

class IStateMachine
{
public:
  typedef std::shared_ptr<IState> StatePtr;

  virtual void Next() = 0;
  virtual void Previous() = 0;
  virtual StatePtr GetCurrentState() = 0;
  virtual void AddState(StatePtr State) = 0;
  virtual void RunCurrentState() = 0;

  virtual ~IStateMachine() {}
};
}
