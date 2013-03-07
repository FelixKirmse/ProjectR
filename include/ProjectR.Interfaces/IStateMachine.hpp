#pragma once
#include <memory>

namespace ProjectR
{
class IState;

class IStateMachine
{
public:
  virtual void Next() = 0;
  virtual void Previous() = 0;
  virtual std::shared_ptr<IState> const& GetCurrentState() = 0;
  virtual void AddState(std::shared_ptr<IState> const& State) = 0;
  virtual void RunCurrentState() = 0;
  virtual std::shared_ptr<IState> const& GetState(int state) = 0;
  virtual void SetCurrentState(int state) = 0;
  virtual void ClearStates() = 0;
  virtual int GetStateCount() = 0;
  virtual bool FirstStateActive() = 0;

  virtual ~IStateMachine() {}
};
}
