#pragma once
#include "RConsole.hpp"
#include <memory>

namespace ProjectR
{
class Character;
class SpellLister : public RConsole
{
public:
  SpellLister(int x, int y) : RConsole(x, y){}

  virtual void SetPosition(int x, int y) = 0;
  virtual void Draw(std::shared_ptr<Character> const& chara, RConsole* target = GetRootConsole()) = 0;

  virtual ~SpellLister(){}
  static std::shared_ptr<SpellLister> Create();
};
}
