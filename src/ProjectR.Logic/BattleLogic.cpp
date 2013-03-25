#include "BattleLogic.hpp"
#include "StateMachine.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "IdleBattleLogic.hpp"
#include "ConsequenceBattleLogic.hpp"
#include "BattleWonLogic.hpp"
#include "GameOverLogic.hpp"

namespace ProjectR
{
struct BattleLogicImpl : public BattleLogic, public StateMachine
{
  BattleLogicImpl()
    : _battleWonLogic(BattleWonLogic::Create()),
      _gameOverLogic(GameOverLogic::Create())
  {
  }

  void Initialize()
  {
    ClearStates();
    AddState(IdleBattleLogic::Create());
    AddState(ConsequenceBattleLogic::Create());
    AddState(_battleWonLogic);
    AddState(_gameOverLogic);
    SetCurrentState(Idle);
    _initialized = true;
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    SetCurrentState(Model()->GetBattleModel()->GetCurrentState());
    RunCurrentState();
    Model()->CommitChanges();

    if(_battleWonLogic->BattleOver())
    {
       Master()->Previous();
       Model()->GetBattleModel()->SetExperienceEarned(0);
    }

    if(_gameOverLogic->GameOver())
    {
      Master()->SetCurrentState(0);
    }
  }

  bool _initialized = false;
  std::shared_ptr<BattleWonLogic> _battleWonLogic;
  std::shared_ptr<GameOverLogic> _gameOverLogic;
};

std::shared_ptr<BattleLogic> BattleLogic::Create()
{
  return std::make_shared<BattleLogicImpl>();
}
}
