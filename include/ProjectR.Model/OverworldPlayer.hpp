#pragma once
#include <memory>

namespace ProjectR
{
class Point;

class OverworldPlayer
{
public:
  virtual Point const& GetPosition() = 0;
  virtual void SetPosition(Point const& position) = 0;

  virtual ~OverworldPlayer(){}
  static std::shared_ptr<OverworldPlayer> Create();
};
}
