#pragma once
#include <memory>

namespace ProjectR
{
class ISpell;
class RConsole;

class SpellDescriptionDrawer
{
public:
  virtual void SetPosition(int x, int y) = 0;
  virtual void DrawSpellDescription(std::shared_ptr<ISpell> const& spell, RConsole* target = nullptr) = 0;

  virtual ~SpellDescriptionDrawer(){}
  static std::shared_ptr<SpellDescriptionDrawer> Create();
};
}
