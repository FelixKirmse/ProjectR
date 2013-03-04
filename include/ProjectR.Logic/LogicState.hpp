#pragma once
#include "ModelState.hpp"

namespace ProjectR
{
class RInput;
class LogicState : public ModelState
{
public:
  virtual ~LogicState(){}
  static inline void SetInput(std::shared_ptr<RInput> const& input){ _input = input; }

protected:
  static inline std::shared_ptr<RInput> const& Input() { return _input; }

private:
  static std::shared_ptr<RInput> _input;
};
}
