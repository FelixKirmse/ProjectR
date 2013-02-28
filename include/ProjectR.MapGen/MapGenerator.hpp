#pragma once
#include <memory>

namespace ProjectR
{
class RMap;

class MapGenerator
{
public:
  MapGenerator(std::shared_ptr<RMap> map);
  ~MapGenerator();

  void GenerateMap(int level);
private:
  class MapGenImpl* _;
};
}
