#pragma once
#include "StateMachine.hpp"

namespace ProjectR
{
class IModel;
class RLogic : public StateMachine
{
public:
  virtual void SetModel(std::shared_ptr<IModel> const& model) = 0;
  static std::shared_ptr<RLogic> Create();
  virtual ~RLogic(){}
};
}
