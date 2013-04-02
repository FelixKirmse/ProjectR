#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class SpellSelectView : public ModelState
{
public:
  virtual ~SpellSelectView(){}
  static std::shared_ptr<SpellSelectView> Create();
};
}
