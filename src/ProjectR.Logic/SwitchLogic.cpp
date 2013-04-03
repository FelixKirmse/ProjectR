#include "SwitchLogic.hpp"
#include "StateMachine.hpp"
#include "MenuModel.hpp"
#include "FrontRowSelector.hpp"
#include "BackRowSelector.hpp"
#include "Initializeable.hpp"

namespace ProjectR
{
struct SwitchLogicImpl : public SwitchLogic, public StateMachine, public Initializeable
{
  void Previous()
  {
    if(FirstStateActive())
      Master()->SetCurrentState(SelectAction);
    else
      StateMachine::Previous();
  }

  void Initialize()
  {
    AddState(FrontRowSelector::Create());
    AddState(BackRowSelector::Create());
    SetCurrentState(0);
  }

  void Activate()
  {
    Init();
  }

  void Run()
  {
    RunCurrentState();
  }
};

std::shared_ptr<SwitchLogic> SwitchLogic::Create()
{
  return std::make_shared<SwitchLogicImpl>();
}
}
