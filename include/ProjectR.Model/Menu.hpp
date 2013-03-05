#pragma once
#include "StateMachine.hpp"
#include "IState.hpp"

namespace ProjectR
{
class Menu : public StateMachine, public IState
{
public:
  virtual ~Menu();

  virtual void Activate();
  virtual void Deactivate();
  virtual void Next();
  virtual void Previous();

private:
  void Run();
  void SetStateMachine(std::shared_ptr<IStateMachine> const& machine);
};
}
