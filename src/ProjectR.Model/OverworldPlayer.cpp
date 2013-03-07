#include "OverworldPlayer.hpp"
#include "Rectangle.hpp"

namespace ProjectR
{
struct PlayerImpl : public OverworldPlayer
{
  PlayerImpl()
    : _position(0, 0)
  {
  }

  Point const& GetPosition()
  {
    return _position;
  }

  void SetPosition(Point const& position)
  {
    if(position == _position)
      return;

    _position = position;
  }

  Point _position;
};

std::shared_ptr<OverworldPlayer> OverworldPlayer::Create()
{
  return std::make_shared<PlayerImpl>();
}
}
