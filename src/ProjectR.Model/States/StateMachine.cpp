#include "StateMachine.hpp"
#include "ISynchronizer.hpp"
#include "IState.hpp"

namespace ProjectR
{
StateMachine::StateMachine()
  : _states(), _currentState(0), _synchronizer()
{
}

int StateMachine::GetStateCount()
{
  return _states.size();
}

void StateMachine::Next()
{
  Sync(_currentState + 1);
  if(_synchronizer != nullptr)
    _synchronizer->Sync(_currentState);
}

void StateMachine::Previous()
{
  Sync(_currentState - 1);
  if(_synchronizer != nullptr)
    _synchronizer->Sync(_currentState);
}

bool StateMachine::FirstStateActive()
{
  return _currentState == 0;
}

std::shared_ptr<IState> const& StateMachine::GetCurrentState()
{
  return _states[_currentState];
}

void StateMachine::AddState(std::shared_ptr<IState> const& state)
{
  state->SetStateMachine(shared_from_this());
  _states.push_back(state);
}

void StateMachine::RunCurrentState()
{
  _states[_currentState]->Run();
  if(_synchronizer != nullptr)
    _synchronizer->Sync(_currentState);
}

void StateMachine::SetCurrentState(int state)
{
  _currentState = state;
  if(_synchronizer != nullptr)
    _synchronizer->Sync(_currentState);
}

void StateMachine::Sync(int value)
{
  if(_currentState == value)
    return;

  _states[_currentState]->Deactivate();
  _currentState = value;
  _states[_currentState]->Activate();
}

void StateMachine::SetSynchronizer(std::shared_ptr<ISynchronizer<int> > const& syncer)
{
  _synchronizer = syncer;
}

std::shared_ptr<IState> const& StateMachine::GetState(int state)
{
  return _states[state];
}

void StateMachine::ClearStates()
{
  _states.clear();
}

}
