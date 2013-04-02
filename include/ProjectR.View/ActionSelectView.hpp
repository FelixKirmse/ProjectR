#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class ActionSelectView : public ModelState
{
public:
  virtual ~ActionSelectView(){}
  static std::shared_ptr<ActionSelectView> Create();
};
}
