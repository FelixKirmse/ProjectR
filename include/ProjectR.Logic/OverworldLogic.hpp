#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class OverworldLogic : public LogicState
{
public:
  virtual ~OverworldLogic(){}
  static std::shared_ptr<OverworldLogic> Create();
};
}
