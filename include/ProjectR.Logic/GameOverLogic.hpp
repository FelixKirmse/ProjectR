#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class GameOverLogic : public LogicState
{
public:
  virtual bool GameOver() = 0;
  virtual ~GameOverLogic(){}
  static std::shared_ptr<GameOverLogic> Create();
};
}
