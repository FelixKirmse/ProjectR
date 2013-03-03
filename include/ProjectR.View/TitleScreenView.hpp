#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class TitleScreenView : public ModelState
{
public:
  static TitleScreenView* Create();
  virtual ~TitleScreenView(){}
};
}
