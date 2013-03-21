#pragma once
#include "TargetInfo.hpp"
#include <memory>

namespace ProjectR
{
class BattleModel;
class CharacterSpellSelect
{
public:
  TargetInfo SelectSpell(std::shared_ptr<Character> const& character,
                         std::shared_ptr<BattleModel> const& battleModel,
                         bool isEnemy);
};
}
