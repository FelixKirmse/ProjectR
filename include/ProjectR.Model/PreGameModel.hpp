#pragma once
#include <memory>

namespace ProjectR
{
class InputBuffer;

class PreGameModel
{
public:
  virtual std::shared_ptr<InputBuffer> const& GetInputBuffer() = 0;

  virtual ~PreGameModel(){}
  static std::shared_ptr<PreGameModel> Create();
};
}
