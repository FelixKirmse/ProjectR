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
  virtual ~StateMachine(){}

  virtual void Next();
  virtual void Previous();
  void AddState(std::shared_ptr<IState> const& state);
  void RunCurrentState();
  void Sync(int value);
  void SetSynchronizer(std::shared_ptr<ISynchronizer<int> > const& syncer);
  virtual void SetCurrentState(int state);
  void ClearStates();
  bool FirstStateActive();

  std::shared_ptr<IState> const& GetCurrentState();
  std::shared_ptr<IState> const& GetState(int state);
  int GetStateCount();

private:
  std::vector<std::shared_ptr<IState> > _states;
  int _currentState;
  std::shared_ptr<ISynchronizer<int> > _synchronizer;
};
}
