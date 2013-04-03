#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class SwitchView : public ModelState
{
public:
  virtual ~SwitchView(){}
  static std::shared_ptr<SwitchView> Create();
};
}
