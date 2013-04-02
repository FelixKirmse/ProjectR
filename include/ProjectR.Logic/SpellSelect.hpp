#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class SpellSelect : public LogicState
{
public:
  virtual ~SpellSelect(){}
  static std::shared_ptr<SpellSelect> Create();
};
}
