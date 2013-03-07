#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class PreGameView : public ModelState
{
public:
  virtual ~PreGameView(){}
  static std::shared_ptr<PreGameView> Create();
};
}
