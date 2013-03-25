#include "BattleWonLogic.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "Party.hpp"
#include "Character.hpp"
#include "Stats.hpp"
#include "RInput.hpp"

namespace ProjectR
{
struct BattleWonLogicImpl : public BattleWonLogic
{
  void Run()
  {
    auto const& battleModel = Model()->GetBattleModel();

    int xpAwarded = 0;

    xpAwarded += (battleModel->IsBossFight() ? XPFromBoss : battleModel->GetDeadCountEnemy() * XPPerEnemy);

    auto const& party = Model()->GetParty();
    xpAwarded /= party->GetAveragePartyLvl() - battleModel->GetBattleLvl() == 0 ?
          1 :
          party->GetAveragePartyLvl() - battleModel->GetBattleLvl();

    for(std::shared_ptr<Character> const& chara : party->GetFrontRow())
    {
      chara->GetStats()->ReduceBuffEffectiveness(10);
      chara->UseMP(-50.f);
    }
    party->AddExperience(xpAwarded);
    battleModel->SetExperienceEarned(xpAwarded);
    Model()->CommitChanges();

    do
    {
      Input()->Update();
    }while(!Input()->Action(Confirm));

    _battleOver = true;
  }

  bool BattleOver()
  {
    bool result = _battleOver;
    if(result)
      _battleOver = false;
    return result;
  }

  bool _battleOver;
  int const XPPerEnemy = 500000; // 25
  int const XPPerConvincedEnemy = 50;
  int const XPFromBoss = 4000;
  int const XPFromConvincedBoss = 8000;
};

std::shared_ptr<BattleWonLogic> BattleWonLogic::Create()
{
  return std::make_shared<BattleWonLogicImpl>();
}
}
