#include "MenuDrawer.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"
#include "RConsole.hpp"

namespace ProjectR
{
struct MenuDrawerImpl : public MenuDrawer
{
  MenuDrawerImpl()
    : _menuConsole(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())
  {
    _menuConsole.SetBackgroundColour(Colour::black);
    _menuConsole.SetForegroundColour(Colour::white);
    _heatZone.X = 0;
    _heatZone.Y = 0;
  }

  void DrawMenu(std::shared_ptr<Menu> const& menu,
                        int row, int col, int offset)
  {
    DrawMenu(menu, row, col, offset, nullptr);
  }

  void DrawMenu(std::shared_ptr<Menu> const& menu,
                RConsole* target,
                int row, int col, int offset)
  {
    DrawMenu(menu, row, col, offset, target);
  }

  void DrawMenu(std::shared_ptr<Menu> const& menu,
                          int row, int col, int offset,
                          RConsole* target)
  {
    if(menu == nullptr)
      return;

    _menuConsole.Clear();
    RConsole* targetConsole = target == nullptr ? RConsole::GetRootConsole() : target;

    int rightMostCol = 0;
    int itemCount = menu->GetStateCount();
    for(int i = 0; i < itemCount; ++i)
    {
      int printRow = i + i * offset;
      std::shared_ptr<MenuItem> item = std::static_pointer_cast<MenuItem>(menu->GetState(i));
      std::string const& label = item->GetLabel();
      int labelLength = label.size();
      if(labelLength > rightMostCol)
        rightMostCol = labelLength;

      if(item->IsSelected())
        _menuConsole.SetForegroundColour(Colour::red);
      else if(item->Disabled())
        _menuConsole.SetForegroundColour(Colour::grey);
      else
        _menuConsole.SetForegroundColour(Colour::white);
      _menuConsole.PrintString(0, printRow, label);
    }

    _heatZone.Width = rightMostCol;
    _heatZone.Height = itemCount + (offset * itemCount);

    targetConsole->Blit(_menuConsole, _heatZone, row, col);
  }

  Rectangle _heatZone;
  RConsole _menuConsole;
};

std::shared_ptr<MenuDrawer> MenuDrawer::Create()
{
  return std::make_shared<MenuDrawerImpl>();
}
}
