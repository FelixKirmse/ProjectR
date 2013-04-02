#include "ActionSelectView.hpp"
#include "MenuDrawer.hpp"
#include "IModel.hpp"
#include "MenuModel.hpp"
#include "Menu.hpp"
#include "StatScreenDrawer.hpp"
#include "BattleModel.hpp"

namespace ProjectR
{
struct ActionSelectViewImpl : public ActionSelectView
{
  ActionSelectViewImpl()
  {

  }

  void Initialize()
  {
    _menuModel = Model()->GetMenuModel();
    _root = RConsole::GetRootConsole();
    _statDrawer->SetPosition(80, 3);
    _initialized = true;
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    auto const& battleMenu = _menuModel->GetBattleMenu();
    if(battleMenu != nullptr)
      _drawer->DrawMenu(battleMenu, 6, 54, 1);


    _root->SetForegroundColour(Colour::white);
    _root->PrintString(3, 52, "Action Select:");
    _root->DrawVerticalLine(19, 52, 12);
    _statDrawer->DrawStats(Model()->GetBattleModel()->GetCurrentAttacker());
  }

  std::shared_ptr<MenuModel> _menuModel = nullptr;
  std::shared_ptr<MenuDrawer> _drawer = MenuDrawer::Create();
  std::shared_ptr<StatScreenDrawer> _statDrawer = StatScreenDrawer::Create();
  RConsole* _root;
  bool _initialized = false;
};

std::shared_ptr<ActionSelectView> ActionSelectView::Create()
{
  return std::make_shared<ActionSelectViewImpl>();
}
}
