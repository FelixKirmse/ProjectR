#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class PreGameLogic : public LogicState
{
public:
  virtual ~PreGameLogic(){}
  static std::shared_ptr<PreGameLogic> Create();
};
}
