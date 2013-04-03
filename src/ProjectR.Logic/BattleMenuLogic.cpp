#include "BattleMenuLogic.hpp"
#include "IModel.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"
#include "MenuController.hpp"
#include "BattleModel.hpp"
#include "Character.hpp"
#include "Spell.hpp"
#include "ActionSelect.hpp"
#include "MenuModel.hpp"
#include "TargetSelect.hpp"
#include "SpellSelect.hpp"
#include "SwitchLogic.hpp"

namespace ProjectR
{
struct MenuLogic : public BattleMenuLogic, public StateMachine
{
  MenuLogic()
  {
  }

  void Initialize()
  {
    AddState(ActionSelect::Create());
    AddState(TargetSelect::Create());
    AddState(SpellSelect::Create());
    AddState(SwitchLogic::Create());
    AddState(/*Convince*/nullptr);
    AddState(/*Execute*/nullptr);
    SetCurrentState(SelectAction);
    _initialized = true;
  }

  void SetCurrentState(int state)
  {
    Model()->GetMenuModel()->SetBattleMenuState(state);
    StateMachine::SetCurrentState(state);
    _lastState = GetCurrentState();
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    auto const& currentState = GetState(Model()->GetMenuModel()->GetBattleMenuState());
    if(currentState != _lastState)
    {
      _lastState->Deactivate();
      currentState->Activate();
    }

    currentState->Run();

    if(Model()->GetMenuModel()->GetBattleMenuState() == Execute)
    {
      Model()->GetBattleModel()->SetCurrentState(Consequences);
      SetCurrentState(SelectAction);
    }

    _lastState = currentState;
  }

  std::shared_ptr<IState> _lastState;

  bool _initialized = false;
};

std::shared_ptr<BattleMenuLogic> BattleMenuLogic::Create()
{
  return std::make_shared<MenuLogic>();
}
}
