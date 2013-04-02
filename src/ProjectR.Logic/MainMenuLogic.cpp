#include "MainMenuLogic.hpp"
#include "IModel.hpp"
#include "RInput.hpp"
#include "Menu.hpp"
#include "MenuModel.hpp"
#include "MenuController.hpp"
#include "MainMenu.hpp"
#include "MenuItem.hpp"
#include "ProjectR.hpp"

namespace ProjectR
{
struct MainMenuLogicImpl : public MainMenuLogic
{
  MainMenuLogicImpl()
    : _mainMenuStateMachine(new StateMachine()),
      _menuController(MenuController::Create())
  {
    _mainMenuStateMachine->AddState(Model()->GetMenuModel()->GetMainMenu());
    _mainMenuStateMachine->AddState(Model()->GetMenuModel()->GetOptionsMenu());

    auto mainMenu = Model()->GetMenuModel()->GetMainMenu();
    std::static_pointer_cast<MenuItem>(mainMenu->GetState(Quit))->SetCallBack(&ProjectR::Exit);
    std::static_pointer_cast<MenuItem>(mainMenu->GetState(Options))->SetCallBack([&](){NextState();});
    std::static_pointer_cast<MenuItem>(mainMenu->GetState(LoadGame))->Disabled(true);
    std::static_pointer_cast<MenuItem>(mainMenu->GetState(NewGame))->SetCallBack([&](){Master()->Next();});
  }

  void NextState()
  {
    _mainMenuStateMachine->Next();
  }

  void CancelAction()
  {
    if(_mainMenuStateMachine->FirstStateActive())
      ProjectR::Exit();
    else
      _mainMenuStateMachine->Previous();
  }

  void Activate()
  {
    Model()->GetMenuModel()->GetMainMenu()->Activate();
    _mainMenuStateMachine->SetCurrentState(0);
  }

  void Run()
  {
    auto const& state = _mainMenuStateMachine->GetCurrentState();

    _menuController->ControlMenu(std::static_pointer_cast<Menu>(state),
                                 Input(),
                                 [&](){CancelAction();});
    Model()->GetMenuModel()->SetActiveMenu(std::static_pointer_cast<Menu>(_mainMenuStateMachine->GetCurrentState()));
    Model()->CommitChanges();
  }

  std::shared_ptr<StateMachine> _mainMenuStateMachine;
  std::shared_ptr<MenuController> _menuController;
  bool _firstTime = true;
};

std::shared_ptr<MainMenuLogic> MainMenuLogic::Create()
{
  return std::make_shared<MainMenuLogicImpl>();
}
}
