#include "BattleMenuView.hpp"
#include "StateMachine.hpp"
#include "IModel.hpp"
#include "MenuModel.hpp"
#include "ActionSelectView.hpp"
#include "TargetSelectView.hpp"
#include "SpellSelectView.hpp"
#include "SwitchView.hpp"

namespace ProjectR
{
struct BattleMenuViewImpl : public BattleMenuView, public StateMachine
{
  void Initialize()
  {
    AddState(ActionSelectView::Create());
    AddState(TargetSelectView::Create());
    AddState(SpellSelectView::Create());
    AddState(SwitchView::Create());
    AddState(/*Convince*/nullptr);
    AddState(/*Execute*/nullptr);
    _initialized = true;
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    int state = Model()->GetMenuModel()->GetBattleMenuState();
    switch(state)
    {

      case Execute:
        break;
      case Convince:
        break;      
      case Switch:       
      case SelectTarget:              
      case SelectSpell:       
      case SelectAction:
        GetState(SelectAction)->Run();
      default:
        break;
    }

    auto const& stateObj = GetState(state);
    if(stateObj != nullptr)
      stateObj->Run();
  }

  bool _initialized = false;
};

std::shared_ptr<BattleMenuView> BattleMenuView::Create()
{
  return std::make_shared<BattleMenuViewImpl>();
}
}
