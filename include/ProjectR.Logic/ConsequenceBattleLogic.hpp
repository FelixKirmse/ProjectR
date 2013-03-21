#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class ConsequenceBattleLogic : public ModelState
{
public:
  static std::shared_ptr<ConsequenceBattleLogic> Create();
  virtual ~ConsequenceBattleLogic(){}
};
}
