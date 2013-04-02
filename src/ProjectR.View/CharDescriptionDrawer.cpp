#include "CharDescriptionDrawer.hpp"
#include "Character.hpp"

namespace ProjectR
{
struct CharDescriptionDrawerImpl : public CharDescriptionDrawer
{
  CharDescriptionDrawerImpl()
    : CharDescriptionDrawer(37, 39)
  {
  }

  void SetPosition(int x, int y)
  {
    posX = x;
    posY = y;
  }

  void DrawSummary(std::shared_ptr<Character> const& chara, RConsole* target)
  {
    if(chara == nullptr)
      return;

    RConsole* targetConsole = target == nullptr ? GetRootConsole() : target;
    Clear();
    DrawBorder();
    PrintString(1, 1, "Name:");
    PrintString(4, 3, chara->GetName());
    PrintString(1, 5, "Race:");
    PrintString(4, 7, chara->GetRace());
    PrintString(1, 9, "Lore:");
    PrintString(Rectangle(4, 11, 32, 19), chara->GetLore());
    targetConsole->Blit(*this, GetBounds(), posX, posY);
  }

  int posX, posY;
};

std::shared_ptr<CharDescriptionDrawer> CharDescriptionDrawer::Create()
{
  return std::make_shared<CharDescriptionDrawerImpl>();
}
}
