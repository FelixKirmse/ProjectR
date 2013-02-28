#pragma once
#include <vector>
#include "IStateMachine.hpp"
#include "ISynchronizeable.hpp"

namespace ProjectR
{
class StateMachine : public IStateMachine, public ISynchronizeable<int>
{
public:
  StateMachine();
  virtual ~StateMachine() = 0;

  void Next();
  void Previous();
  StatePtr GetCurrentState();
  void AddState(StatePtr state);
  void RunCurrentState();
  void Sync(int value);
  void SetSynchronizer(std::shared_ptr<ISynchronizer<int> > syncer);

private:
  std::vector<StatePtr> _states;
  int _currentState;
  std::shared_ptr<ISynchronizer<int> > _synchronizer;
};
}
