#pragma once
#include <memory>

namespace ProjectR
{
class ISpell;
class Character;

struct TargetInfo
{
  enum TargetType
  {
    Single = 0,
    Myself = 1,
    Allies = 2,
    Enemies = 3,
    Decaying = 4
  };
  std::shared_ptr<Character> Target;
  std::shared_ptr<ISpell> Spell;
};
}
