#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class BattleWonView : public ModelState
{
public:
  virtual ~BattleWonView(){}
  static std::shared_ptr<BattleWonView> Create();
};
}
