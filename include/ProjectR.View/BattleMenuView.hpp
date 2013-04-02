#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class BattleMenuView : public ModelState
{
public:
  virtual ~BattleMenuView(){}
  static std::shared_ptr<BattleMenuView> Create();
};
}
