#pragma once
#include <memory>

namespace ProjectR
{
class RMap;

class MapGenerator
{
public:
  virtual void GenerateMap(int level) = 0;
  static std::shared_ptr<MapGenerator> Create(std::shared_ptr<RMap> const& map);
  virtual ~MapGenerator(){}
};
}
