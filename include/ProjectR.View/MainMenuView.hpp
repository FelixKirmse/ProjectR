#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class MainMenuView : public ModelState
{
public:
  static std::shared_ptr<MainMenuView> Create();
  virtual ~MainMenuView(){}
};
}
