#include "MainMenuView.hpp"
#include "IModel.hpp"
#include "MenuModel.hpp"
#include "MenuDrawer.hpp"
#include "RConsole.hpp"

namespace ProjectR
{
struct MainMenuViewImpl : public MainMenuView
{
  MainMenuViewImpl()
    :  _root(RConsole::GetRootConsole()),
      _menuDrawer(MenuDrawer::Create()),
      _rootWidth(_root->GetWidth()),
      _rootHeight(_root->GetHeight()),
      _menuConsole(9, 4)
  {
  }

  void Run()
  {
    _root->Clear();
    _menuDrawer->DrawMenu(Model()->GetMenuModel()->GetActiveMenu(), 0, 0, &_menuConsole);
    _root->Blit(_menuConsole, _menuConsole.GetBounds(), 5, _rootHeight - 9);
  }

  RConsole* _root;
  std::shared_ptr<MenuDrawer> _menuDrawer;
  int _rootWidth;
  int _rootHeight;
  RConsole _menuConsole;
};

std::shared_ptr<MainMenuView> MainMenuView::Create()
{
  return std::make_shared<MainMenuViewImpl>();
}
}
