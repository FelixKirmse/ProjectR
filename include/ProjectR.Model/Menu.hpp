#pragma once
#include "StateMachine.hpp"
#include "IState.hpp"

namespace ProjectR
{
class MenuItem;

class Menu : public StateMachine, public IState
{
public:
  virtual ~Menu();

  virtual void Activate();
  virtual void Deactivate();
  virtual void Next();
  virtual void Previous();

  virtual void Run();

private:  
  void SetStateMachine(std::shared_ptr<IStateMachine> const& machine);
};
}
