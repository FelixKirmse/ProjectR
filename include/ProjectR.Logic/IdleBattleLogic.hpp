#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class IdleBattleLogic : public ModelState
{
public:
  static std::shared_ptr<IdleBattleLogic> Create();
  virtual ~IdleBattleLogic(){}
};
}
