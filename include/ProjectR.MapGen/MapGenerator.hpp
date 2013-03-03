#pragma once
#include <memory>

namespace ProjectR
{
class RMap;

class MapGenerator
{
public:
  virtual void GenerateMap(int level) = 0;
  static MapGenerator* Create(std::shared_ptr<RMap> map);
  virtual ~MapGenerator(){}
};
}
