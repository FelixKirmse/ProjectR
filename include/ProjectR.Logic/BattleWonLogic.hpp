#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class BattleWonLogic : public LogicState
{
public:
  virtual bool BattleOver() = 0;
  virtual ~BattleWonLogic(){}
  static std::shared_ptr<BattleWonLogic> Create();
};
}
