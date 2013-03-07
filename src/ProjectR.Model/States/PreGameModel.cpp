#include "PreGameModel.hpp"
#include "InputBuffer.hpp"

namespace ProjectR
{
struct PreGameModelImpl : public PreGameModel
{
  PreGameModelImpl()
    : _inputBuffer(InputBuffer::Create())
  {
  }

  std::shared_ptr<InputBuffer> const& GetInputBuffer()
  {
    return _inputBuffer;
  }

  std::shared_ptr<InputBuffer> _inputBuffer;
};

std::shared_ptr<PreGameModel> PreGameModel::Create()
{
  return std::make_shared<PreGameModelImpl>();
}
}
