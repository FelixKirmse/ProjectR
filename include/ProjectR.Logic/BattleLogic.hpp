#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class BattleLogic : public LogicState
{
public:
  virtual ~BattleLogic(){}
  static std::shared_ptr<BattleLogic> Create();
};
}
