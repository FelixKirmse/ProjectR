#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class TargetSelect : public LogicState
{
public:
  virtual ~TargetSelect(){}
  static std::shared_ptr<TargetSelect> Create();
};
}
