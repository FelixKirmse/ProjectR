#include "MainMenuView.hpp"
#include "IModel.hpp"
#include "MainMenu.hpp"
#include "MenuModel.hpp"
#include "RConsole.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"

namespace ProjectR
{
struct MainMenuViewImpl : public MainMenuView
{
  MainMenuViewImpl()
  {
  }

  void Run()
  {
    RConsole::GetRootConsole()->SetBackgroundColour(Colour::black);
    RConsole::GetRootConsole()->SetForegroundColour(Colour::white);
    TCODConsole::root->clear();
    std::shared_ptr<MenuItem> menu = std::static_pointer_cast<MenuItem>(Model()->GetMenuModel()->GetMainMenu()->GetCurrentState());

    TCODConsole::root->print(10, 10, menu->GetLabel().c_str());
  }
};

std::shared_ptr<MainMenuView> MainMenuView::Create()
{
  return std::make_shared<MainMenuViewImpl>();
}
}
