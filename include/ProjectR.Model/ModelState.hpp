#pragma once
#include "IState.hpp"

namespace ProjectR
{
class IModel;
class ModelState : public IState
{
public:
  virtual ~ModelState(){}
  virtual void Activate();
  virtual void Deactivate();
  void SetStateMachine(std::shared_ptr<IStateMachine> const& machine);

  inline static void SetModel(std::shared_ptr<IModel> const& model) { _model = model; }

protected:
  std::shared_ptr<IStateMachine> const& Master();
  inline static std::shared_ptr<IModel> Model(){ return _model; }

private:
  std::shared_ptr<IStateMachine> _masterMachine;
  static std::shared_ptr<IModel> _model;
};
}
