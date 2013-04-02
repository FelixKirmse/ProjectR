#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class BattleMenuLogic : public LogicState
{
public:
  virtual ~BattleMenuLogic(){}
  static std::shared_ptr<BattleMenuLogic> Create();
};
}
