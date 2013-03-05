#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class MainMenuLogic : public LogicState
{
public:
  static std::shared_ptr<MainMenuLogic> Create();
  virtual ~MainMenuLogic(){}
};
}
