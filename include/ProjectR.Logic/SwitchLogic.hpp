#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class SwitchLogic : public LogicState
{
public:
  virtual ~SwitchLogic(){}
  static std::shared_ptr<SwitchLogic> Create();
};
}
