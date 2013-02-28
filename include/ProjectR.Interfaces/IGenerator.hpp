#pragma once
#include "Direction.hpp"

namespace ProjectR
{
class IGenerator
{
public:
  virtual bool Generate(int row, int col, Direction dir) = 0;

  virtual ~IGenerator() {}
};
}
