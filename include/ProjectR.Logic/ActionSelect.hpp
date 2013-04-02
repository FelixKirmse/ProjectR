#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class ActionSelect : public LogicState
{
public:
  virtual ~ActionSelect(){}
  static std::shared_ptr<ActionSelect> Create();
};
}
