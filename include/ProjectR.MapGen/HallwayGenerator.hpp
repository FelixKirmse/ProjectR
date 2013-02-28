#pragma once
#include "Generator.hpp"

namespace ProjectR
{
class HallwayGenerator : public Generator
{
public:
  HallwayGenerator(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map);

protected:
  void GenerateImpl(int row, int col, Direction dir);
};
}
