#include "SpellLister.hpp"
#include "ISpell.hpp"
#include "Character.hpp"

namespace ProjectR
{
struct SpellListerImpl : public SpellLister
{
  SpellListerImpl()
    : SpellLister(37, 21)
  {
  }

  void SetPosition(int x, int y)
  {
    posX = x;
    posY = y;
  }

  void Draw(std::shared_ptr<Character> const& chara, RConsole* target)
  {
    Clear();
    DrawBorder();
    SetColourControl(TCOD_COLCTRL_1, Colour::red);
    PrintString(1, 1, "%cSpelllist:%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    int row = 1;
    for(auto const& spell : chara->GetSpells())
    {
      row += 2;
      PrintString(1, row, spell->GetName());
    }
    target->Blit(*this, GetBounds(), posX, posY);
  }

  int posX = 0;
  int posY = 0;
};

std::shared_ptr<SpellLister> SpellLister::Create()
{
  return std::make_shared<SpellListerImpl>();
}
}
