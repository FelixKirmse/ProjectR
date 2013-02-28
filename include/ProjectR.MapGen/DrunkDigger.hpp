#pragma once
#include "Generator.hpp"

namespace ProjectR
{
class DrunkDigger : public Generator
{
public:
  DrunkDigger(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map);

protected:
  void GenerateImpl(int row, int col, Direction dir);
};
}
