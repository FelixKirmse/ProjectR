#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class TitleScreenView : public ModelState
{
public:
  static std::shared_ptr<TitleScreenView> Create();
  virtual ~TitleScreenView(){}
};
}
