#include "ModelState.hpp"

namespace ProjectR
{
std::shared_ptr<IModel> ModelState::_model;
void ModelState::SetModel(std::shared_ptr<IModel> const& model)
{
  _model = model;  
}

std::shared_ptr<IModel> const& ModelState::Model()
{
  return _model;
}

void ModelState::Activate()
{
}

void ModelState::Deactivate()
{
}

void ModelState::SetStateMachine(const std::shared_ptr<IStateMachine> &machine)
{
  _masterMachine = machine;
}

std::shared_ptr<IStateMachine> const& ModelState::Master()
{
  return _masterMachine;
}
}
