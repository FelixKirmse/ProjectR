#include "IdleBattleLogic.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "Character.hpp"
#include "CharacterSpellSelect.hpp"

namespace ProjectR
{
struct IdleBattleLogicImpl : public IdleBattleLogic
{
  void Run()
  {
    auto battleModel = Model()->GetBattleModel();
    auto frontRow = battleModel->GetFrontRow();

    if(_lastAttacker != nullptr)
      _lastAttacker->TurnEnded();

    for(int i = _playerLeftOff; i < (int)frontRow.size(); ++i)
    {
      if(!frontRow[i]->UpdateTurnCounter())
        continue;

      battleModel->SetCurrentState(BattleMenu);
      _playerLeftOff = i + 1;
      battleModel->SetCurrentAttacker(frontRow[i]);
      battleModel->IsEnemyTurn(false);
      _lastAttacker = frontRow[i];
      return;
    }

    _playerLeftOff = 0;

    UpdateAI(battleModel->GetPlayerMinions(), _playerMinionLeftOff, false, battleModel);
    UpdateAI(battleModel->GetEnemies(), _enemyLeftOff, true, battleModel);
    UpdateAI(battleModel->GetEnemyMinions(), _enemyMinionLeftOff, true, battleModel);
  }

  void UpdateAI(std::vector<std::shared_ptr<Character> >& vec, int& counter, bool enemyTurn,
                std::shared_ptr<BattleModel> const& battleModel)
  {
    for(int i = counter; i < (int)vec.size(); ++i)
    {
      if(!vec[i]->UpdateTurnCounter())
        continue;

      battleModel->SetTargetInfo(_spellSelect.SelectSpell(vec[i], battleModel, enemyTurn));
      counter = i + 1;
      battleModel->SetCurrentState(Consequences);
      battleModel->SetCurrentAttacker(vec[i]);
      battleModel->IsEnemyTurn(enemyTurn);
      _lastAttacker = vec[i];
      return;
    }

    counter = 0;
  }

  CharacterSpellSelect _spellSelect;
  int _playerLeftOff = 0;
  int _enemyLeftOff = 0;
  int _enemyMinionLeftOff = 0;
  int _playerMinionLeftOff = 0;  
  std::shared_ptr<Character> _lastAttacker = nullptr;
};

std::shared_ptr<IdleBattleLogic> IdleBattleLogic::Create()
{
  return std::make_shared<IdleBattleLogicImpl>();
}
}
