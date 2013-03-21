#include "BattleLogic.hpp"
#include "StateMachine.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "IdleBattleLogic.hpp"
#include "ConsequenceBattleLogic.hpp"

namespace ProjectR
{
struct BattleLogicImpl : public BattleLogic, public StateMachine
{
  BattleLogicImpl()
  {

  }

  void Initialize()
  {
    ClearStates();
    AddState(IdleBattleLogic::Create());
    AddState(ConsequenceBattleLogic::Create());
    SetCurrentState(Idle);
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    SetCurrentState(Model()->GetBattleModel()->GetCurrentState());
    RunCurrentState();
    Model()->CommitChanges();
  }

  bool _initialized = false;
};

std::shared_ptr<BattleLogic> BattleLogic::Create()
{
  return std::make_shared<BattleLogicImpl>();
}
}
