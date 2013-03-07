#pragma once
#include <string>
#include <memory>

namespace ProjectR
{
class InputBuffer
{
public:
  virtual void AddChar(char character) = 0;
  virtual void RemoveChar() = 0;

  virtual std::string GetString() = 0;
  virtual void Reset() = 0;
  virtual int GetLength() = 0;

  virtual ~InputBuffer(){}
  static std::shared_ptr<InputBuffer> Create();
};
}
