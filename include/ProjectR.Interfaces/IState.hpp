#pragma once
#include <memory>

namespace ProjectR
{
class IStateMachine;

class IState
{
public:
  virtual void Activate() = 0;
  virtual void Deactivate() = 0;
  virtual void Run() = 0;

  virtual void SetStateMachine(std::shared_ptr<IStateMachine> machine) = 0;

  virtual ~IState() {}
};
}
