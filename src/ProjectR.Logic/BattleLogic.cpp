#include "BattleLogic.hpp"
#include "StateMachine.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "IdleBattleLogic.hpp"
#include "ConsequenceBattleLogic.hpp"
#include "BattleWonLogic.hpp"
#include "GameOverLogic.hpp"
#include "Party.hpp"
#include "CharacterFactory.hpp"
#include "Character.hpp"
#include "BattleMenuLogic.hpp"

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
    AddState(BattleMenuLogic::Create());
    AddState(ConsequenceBattleLogic::Create());
    AddState(_battleWonLogic);
    AddState(_gameOverLogic);
    SetCurrentState(Idle);
    _initialized = true;    
  } 

  void Activate()
  {
    auto const& party = Model()->GetParty();
    auto const& fac = Model()->GetCharacterFactory();
    party->Reset();
    party->AddCharacter(fac->CreateRandomCharacter(5000), FrontRow);
    party->AddCharacter(fac->CreateRandomCharacter(5000), FrontRow);
    party->AddCharacter(fac->CreateRandomCharacter(5000), FrontRow);
    party->AddCharacter(fac->CreateRandomCharacter(5000), FrontRow);

    for(int i = 0; i < 6; ++i)
    {
      party->AddCharacter(fac->CreateRandomCharacter(5000), BackSeat);
    }

    Model()->GetBattleModel()->StartBattle(4000);
  }

  void Run()
  {
    if(!_initialized)
      Initialize();

    SetCurrentState(Model()->GetBattleModel()->GetCurrentState());
    if(GetCurrentState() != nullptr)
      RunCurrentState();
    Model()->CommitChanges();

    if(_battleWonLogic->BattleOver())
    {
       Master()->Previous();
       Master()->Next();
       /*
       Master()->Previous();
       Model()->GetBattleModel()->SetExperienceEarned(0);*/
    }

    if(_gameOverLogic->GameOver())
    {      
      Master()->Previous();
      Master()->Next();
      //Master()->SetCurrentState(0);
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
