#include "StateMachine.hpp"
#include "ISynchronizer.hpp"
#include "IState.hpp"

namespace ProjectR
{
StateMachine::StateMachine()
  : _states(), _currentState(0), _synchronizer()
{
}

StateMachine::~StateMachine() = default;


void StateMachine::Next()
{
  _synchronizer->Sync(_currentState + 1);
}

void StateMachine::Previous()
{
  _synchronizer->Sync(_currentState - 1);
}

StateMachine::StatePtr StateMachine::GetCurrentState()
{
  return _states[_currentState];
}

void StateMachine::AddState(StatePtr state)
{
  state->SetStateMachine(shared_from_this());
  _states.push_back(state);
}

void StateMachine::RunCurrentState()
{
  _states[_currentState]->Run();
}

void StateMachine::Sync(int value)
{
  _states[_currentState]->Deactivate();
  _currentState = value;
  _states[_currentState]->Activate();
}

void StateMachine::SetSynchronizer(std::shared_ptr<ISynchronizer<int> > syncer)
{
  _synchronizer = syncer;
}

}
