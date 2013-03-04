#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class TitleScreenLogic : public LogicState
{
public:
  static std::shared_ptr<TitleScreenLogic> Create();
  virtual ~TitleScreenLogic(){}
};
}
