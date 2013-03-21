#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class BattleView : public ModelState
{
public:
  static std::shared_ptr<BattleView> Create();
  virtual ~BattleView(){}
};
}
