#pragma once
#include <memory>
#include "ModelState.hpp"

namespace ProjectR
{
class BattleLogDrawer : public ModelState
{
public:
  virtual void SetPosition(int x, int y) = 0;

  virtual ~BattleLogDrawer(){}
  static std::shared_ptr<BattleLogDrawer> Create();
};
}
