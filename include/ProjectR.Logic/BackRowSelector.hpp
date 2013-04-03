#pragma once
#include "LogicState.hpp"

namespace ProjectR
{
class BackRowSelector : public LogicState
{
public:
  virtual ~BackRowSelector(){}
  static std::shared_ptr<BackRowSelector> Create();
};
}
