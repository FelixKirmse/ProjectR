#include "BattleView.hpp"
#include "IModel.hpp"
#include "StateMachine.hpp"
#include "BattleModel.hpp"
#include "BattleWonView.hpp"

namespace ProjectR
{
struct BattleViewImpl : public BattleView, public StateMachine
{
  BattleViewImpl()
  {
  }

  void Initialize()
  {
    ClearStates();
    AddState(BattleWonView::Create());
    SetCurrentState(Idle);
    _initialized = true;
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    SetCurrentState(Model()->GetBattleModel()->GetCurrentState());
    RunCurrentState();
  }

  bool _initialized = false;
};

std::shared_ptr<BattleView> BattleView::Create()
{
  return std::make_shared<BattleViewImpl>();
}
}
