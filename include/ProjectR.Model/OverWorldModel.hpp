#pragma once
#include <memory>

namespace ProjectR
{
class OverworldPlayer;

class OverWorldModel
{
public:
  OverWorldModel();

  std::shared_ptr<OverworldPlayer> GetPlayer() { return _player; }

private:
  std::shared_ptr<OverworldPlayer> _player;
};
}
