#include "ModelState.hpp"

namespace ProjectR
{
std::shared_ptr<IModel> ModelState::_model;

void ModelState::Activate()
{
}

void ModelState::Deactivate()
{
}

void ModelState::SetStateMachine(std::shared_ptr<IStateMachine> const& machine)
{
  _masterMachine = machine;
}

std::shared_ptr<IStateMachine> const& ModelState::Master()
{
  return _masterMachine;
}
}
