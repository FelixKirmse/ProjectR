#include "OverWorldModel.hpp"
#include "OverworldPlayer.hpp"

namespace ProjectR
{
OverWorldModel::OverWorldModel()
  : _player(OverworldPlayer::Create())
{
}
}
