#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class FrontRowSelector : public LogicState
{
public:
  virtual ~FrontRowSelector(){}
  static std::shared_ptr<FrontRowSelector> Create();
};
}
