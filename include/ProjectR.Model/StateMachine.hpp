#pragma once
#include <vector>
#include "IStateMachine.hpp"
#include "ISynchronizeable.hpp"

namespace ProjectR
{
class StateMachine : public IStateMachine, public ISynchronizeable<int>,
    public std::enable_shared_from_this<StateMachine>
{
public:
  StateMachine();
  virtual ~StateMachine() = 0;

  void Next();
  void Previous();
  std::shared_ptr<IState> const& GetCurrentState();
  void AddState(std::shared_ptr<IState> const& state);
  void RunCurrentState();
  void Sync(int value);
  void SetSynchronizer(std::shared_ptr<ISynchronizer<int> > const& syncer);

private:
  std::vector<std::shared_ptr<IState> > _states;
  int _currentState;
  std::shared_ptr<ISynchronizer<int> > _synchronizer;
};
}
