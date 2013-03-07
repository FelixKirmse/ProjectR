#pragma once
#include <memory>
#include "Input.hpp"

namespace ProjectR
{
enum Actions
{
  None,
  Up,
  Down,
  Left,
  Right,
  Confirm,
  Cancel,
  Inventory,
  Party,
  Back
};

class RInput : public Input<int>
{
public:
  static std::shared_ptr<RInput> Create();
  virtual ~RInput() = 0;
};
}
