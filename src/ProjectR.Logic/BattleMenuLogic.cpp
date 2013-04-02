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
    AddState(/*Switch*/nullptr);
    AddState(/*Convince*/nullptr);
    AddState(/*Execute*/nullptr);
    SetCurrentState(SelectAction);
    _initialized = true;
  }

  void SetCurrentState(int state)
  {
    Model()->GetMenuModel()->SetBattleMenuState(state);
    StateMachine::SetCurrentState(state);
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    RunCurrentState();

    if(Model()->GetMenuModel()->GetBattleMenuState() == Execute)
    {
      Model()->GetBattleModel()->SetCurrentState(Consequences);
      SetCurrentState(SelectAction);
    }
  }

  bool _initialized = false;
};

std::shared_ptr<BattleMenuLogic> BattleMenuLogic::Create()
{
  return std::make_shared<MenuLogic>();
}
}
