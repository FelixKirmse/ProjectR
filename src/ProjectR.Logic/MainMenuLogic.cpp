#include "MainMenuLogic.hpp"
#include "RInput.hpp"
#include "Menu.hpp"
#include "IModel.hpp"
#include "MenuModel.hpp"

namespace ProjectR
{
struct MainMenuLogicImpl : public MainMenuLogic
{
  MainMenuLogicImpl()
  {
  }

  void Activate()
  {
    Model()->GetMenuModel()->GetMainMenu()->Activate();
  }

  void Run()
  {
    auto mainMenu = Model()->GetMenuModel()->GetMainMenu();
    Input()->Update();

    if(Input()->Action(Up))
      mainMenu->Previous();
    else if(Input()->Action(Down))
      mainMenu->Next();
    else if(Input()->Action(Cancel))
      Master()->Previous();
    Model()->CommitChanges();
  }
};

std::shared_ptr<MainMenuLogic> MainMenuLogic::Create()
{
  return std::make_shared<MainMenuLogicImpl>();
}
}
