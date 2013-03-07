#include "InputBuffer.hpp"
#include <sstream>

namespace ProjectR
{
struct InputBufferImpl : public InputBuffer
{
  InputBufferImpl()
    : _pos(0)
  {
  }

  void AddChar(char character)
  {
    _buffer[_pos] = character;
    ++_pos;
  }

  void RemoveChar()
  {
    if(_pos != 0)
      --_pos;
  }

  int GetLength()
  {
    return _pos;
  }

  std::string GetString()
  {
    std::stringstream buffer;
    for(int i = 0; i < _pos; ++i)
      buffer << _buffer[i];
    return buffer.str();
  }

  void Reset()
  {
    _pos = 0;
  }

  char _buffer[255] = {0};
  int _pos;
};

std::shared_ptr<InputBuffer> InputBuffer::Create()
{
  return std::make_shared<InputBufferImpl>();
}
}
