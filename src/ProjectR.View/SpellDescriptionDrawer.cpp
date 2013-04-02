#include "SpellDescriptionDrawer.hpp"
#include "RConsole.hpp"
#include "ISpell.hpp"

namespace ProjectR
{
struct SpellDesc : public SpellDescriptionDrawer, public RConsole
{
  SpellDesc()
    : RConsole(37, 21),
      PrintArea(0, 2, GetWidth(), GetHeight() - 2)
  {
  }

  void SetPosition(int x, int y)
  {
    posX = x;
    posY = y;
  }

  void DrawSpellDescription(std::shared_ptr<ISpell> const& spell, RConsole* target)
  {
    RConsole* targetConsole = target == nullptr ? GetRootConsole() : target;
    Clear();
    SetColourControl(TCOD_COLCTRL_1, Colour::red);
    PrintString(0, 0, "%cSpellDescription%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    PrintString(PrintArea, spell->GetDescription());
    targetConsole->Blit(*this, GetBounds(), posX, posY);
  }

  int posX;
  int posY;
  Rectangle const PrintArea;
};

std::shared_ptr<SpellDescriptionDrawer> SpellDescriptionDrawer::Create()
{
  return std::make_shared<SpellDesc>();
}
}
