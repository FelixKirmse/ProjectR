#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class TargetSelectView : public ModelState
{
public:
  virtual ~TargetSelectView(){}
  static std::shared_ptr<TargetSelectView> Create();
};
}
