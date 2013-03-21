#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class OverworldView : public ModelState
{
public:
  static std::shared_ptr<OverworldView> Create();
  virtual ~OverworldView(){}
};
}
