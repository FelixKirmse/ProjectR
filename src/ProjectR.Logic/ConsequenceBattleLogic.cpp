#include "ConsequenceBattleLogic.hpp"
#include "BattleModel.hpp"
#include "Character.hpp"
#include "IModel.hpp"
#include "ISpell.hpp"
#include "Statistics.hpp"
#include "BattleLog.hpp"
#include "Party.hpp"

namespace ProjectR
{
struct ConsequenceBattleLogicImpl : public ConsequenceBattleLogic
{
  void Run()
  {
    _battleModel = Model()->GetBattleModel();
    _currentAttacker = _battleModel->GetCurrentAttacker();
    _targetInfo = _battleModel->GetTargetInfo();

    _enemyTurn = _battleModel->IsEnemyTurn();
    ++_frameCounter;
    if(_frameCounter == ConsequenceFrames)
    {
      FrameLimitReached();
      return;
    }

    if(_frameCounter > 1)
    {
      FramesCounting();
      return;
    }

    Calculate();
  }

  void Calculate()
  {
    _currentAttacker->UseMP(_targetInfo.Spell->GetMPCost(_currentAttacker));
    bool targetIsEnemy = _battleModel->TargetIsEnemy();

    if(!targetIsEnemy)
      Model()->GetStatistics()->AddToStatistic(Statistics::SpellsCast, 1);

    float charHPBefore[4];
    float enemyHPBefore[4];
    auto const& frontRow = _battleModel->GetFrontRow();
    auto const& enemies = _battleModel->GetEnemies();
    auto const& log = _battleModel->GetBattleLog();
    for(auto i = 0u; i < frontRow.size(); ++i)
    {
      charHPBefore[i] = frontRow[i]->GetCurrentHP();
    }

    for(auto i = 0u; i < enemies.size(); ++i)
    {
      enemyHPBefore[i] = enemies[i]->GetCurrentHP();
    }

    auto targetType = _targetInfo.Spell->GetTargetType();
    switch(targetType)
    {
    case TargetInfo::Single:
      _targetInfo.Spell->DamageCalculation(_currentAttacker, _targetInfo.Target);
      log->LogAction(_currentAttacker, _targetInfo.Target, _targetInfo.Spell);
      _targetInfo.Target->IsMarked(true);
      break;

    case TargetInfo::Myself:
      _targetInfo.Spell->DamageCalculation(_currentAttacker, _currentAttacker);
      log->LogAction(_currentAttacker, _currentAttacker, _targetInfo.Spell);
      _currentAttacker->IsMarked(true);
      break;

    case TargetInfo::Allies:
    case TargetInfo::Enemies:
    {
      bool attackerIsEnemy = _battleModel->AttackerIsEnemy();
      bool targetIsPlayer = (attackerIsEnemy && targetType != TargetInfo::Allies) ||
          (!attackerIsEnemy && targetType == TargetInfo::Allies);

      auto const& targetRow = targetIsPlayer ? frontRow : enemies;
      for(size_t i = 0; i < targetRow.size(); ++i)
      {
        _targetInfo.Spell->DamageCalculation(_currentAttacker, targetRow[i]);
        log->LogAction(_currentAttacker, targetRow[i], _targetInfo.Spell);
        targetRow.at(i)->IsMarked(true);
      }
      break;
    }
    case TargetInfo::Decaying:
    {
      _targetInfo.Spell->DamageCalculation(_currentAttacker, _targetInfo.Target);

      auto const& targetRow = targetIsEnemy ? enemies : frontRow;
      auto const& casterRow = _enemyTurn ? frontRow : enemies;

      size_t attackerIndex = 0;
      for(; attackerIndex < targetRow.size() &&
          (&(*casterRow[attackerIndex]) != &(*_targetInfo.Target));
          ++attackerIndex); // No Body is intended!

      for(int i = attackerIndex - 1, mod = 2; i >= 0; --i, ++mod)
      {
        _targetInfo.Spell->DamageCalculation(_currentAttacker, targetRow[i], mod);
        log->LogAction(_currentAttacker, targetRow[i], _targetInfo.Spell);
        targetRow.at(i)->IsMarked(true);
      }

      for(size_t i = attackerIndex + 1, mod = 2; i < targetRow.size(); ++i, ++mod)
      {
        _targetInfo.Spell->DamageCalculation(_currentAttacker, targetRow[i], mod);
        log->LogAction(_currentAttacker, targetRow[i], _targetInfo.Spell);
        targetRow.at(i)->IsMarked(true);
      }

      break;
    }
    }

    _enemyTurn = false;

    for(size_t i = 0; i < frontRow.size(); ++i)
    {
      float currentHP = frontRow[i]->GetCurrentHP();
      _charHPShouldHave[i] = currentHP;
      _charHPStep[i] = (charHPBefore[i] - currentHP) / ConsequenceFrames;
      frontRow[i]->SetCurrentHP(charHPBefore[i] - _charHPStep[i]);
    }

    for(size_t i = 0; i < enemies.size(); ++i)
    {
      float currentHP = enemies[i]->GetCurrentHP();
      _enemyHPShouldHave[i] = currentHP;
      _enemyHPStep[i] = (enemyHPBefore[i] - currentHP) / ConsequenceFrames;
      enemies[i]->SetCurrentHP(enemyHPBefore[i] - _enemyHPStep[i]);
    }

    auto const& statistics = Model()->GetStatistics();
    for(std::shared_ptr<Character> const& playerChar : frontRow)
    {
      statistics->AddToStatistic(playerChar->WasHealed() ? Statistics::HealingTaken :
                                                           Statistics::DamageTaken,
                                 playerChar->GetDamageTaken());

      if(playerChar->DodgedAttack())
        statistics->AddToStatistic(Statistics::SuccessfulDodges, 1);

      if(playerChar->BlockedDamage())
        statistics->AddToStatistic(Statistics::DamageBlocked, playerChar->GetDamageTaken());
    }

    for(std::shared_ptr<Character> const& enemy : enemies)
    {
      statistics->AddToStatistic(Statistics::DamageDone, enemy->GetDamageTaken());
    }
  }

  void FramesCounting()
  {
    auto const& frontRow = _battleModel->GetFrontRow();
    for(size_t i = 0; i < frontRow.size(); ++i)
    {
      frontRow[i]->SetCurrentHP(frontRow[i]->GetCurrentHP() - _charHPStep[i]);
    }

    auto const& enemies = _battleModel->GetEnemies();
    for(size_t i = 0; i < enemies.size(); ++i)
    {
      enemies[i]->SetCurrentHP(enemies[i]->GetCurrentHP() - _enemyHPStep[i]);
    }
  }

  void FrameLimitReached()
  {
    _battleModel->SetCurrentState(Idle);
    _frameCounter = 0;
    auto const& frontRow = _battleModel->GetFrontRow();
    for(auto i = 0u; i < frontRow.size(); ++i)
    {
      frontRow[i]->SetCurrentHP(_charHPShouldHave[i]);
      frontRow[i]->ResetDamageTaken();
      frontRow.at(i)->IsMarked(false);
    }

    auto const& enemies = _battleModel->GetEnemies();
    for(auto i = 0u; i < enemies.size(); ++i)
    {
      enemies[i]->SetCurrentHP(_enemyHPShouldHave[i]);
      enemies.at(i)->IsMarked(false);
    }

    bool someoneAlive = false;
    std::vector<std::shared_ptr<Character> > toBeDeleted;
    for(std::shared_ptr<Character> const& player : frontRow)
    {
      bool playerDead = player->IsDead();
      if(playerDead)
      {
         toBeDeleted.push_back(player);
         _battleModel->PlayerDied();
      }
      someoneAlive |= !playerDead;
    }

    for(auto const& player : toBeDeleted)
      Model()->GetParty()->RemoveCharacter(player);

    toBeDeleted.clear();

    if(!someoneAlive)
    {
      _battleModel->SetCurrentState(GameOver);
      return;
    }

    bool enemyAlive = false;

    for(std::shared_ptr<Character> const& enemy : enemies)
    {
      enemy->ResetDamageTaken();
      bool enemyDead = enemy->IsDead();
      if(enemyDead)
      {
         toBeDeleted.push_back(enemy);
         _battleModel->EnemyDied();
      }

      enemyAlive |= !enemyDead;
    }

    for(auto const& enemy : toBeDeleted)
      _battleModel->RemoveEnemy(enemy);

    if(!enemyAlive)
    {
      _battleModel->SetCurrentState(BattleWon);
      auto const& statistics = Model()->GetStatistics();
      statistics->AddToStatistic(Statistics::EnemiesKilled, enemies.size());
      int playerDeathCount = 0;
      for(std::shared_ptr<Character> const& player : frontRow)
      {
        if(player->IsDead())
          ++playerDeathCount;
      }
      statistics->AddToStatistic(Statistics::PartyMembersLost, playerDeathCount);
      statistics->AddToStatistic(Statistics::BattlesFought, 1);
    }
  }

  std::shared_ptr<BattleModel> _battleModel;
  std::shared_ptr<Character> _currentAttacker;
  TargetInfo _targetInfo;
  bool _enemyTurn = false;
  int _frameCounter = 0;
  int const ConsequenceFrames = 90;
  float _charHPShouldHave[4];
  float _charHPStep[4];

  float _enemyHPShouldHave[4];
  float _enemyHPStep[4];
};

std::shared_ptr<ConsequenceBattleLogic> ConsequenceBattleLogic::Create()
{
  return std::make_shared<ConsequenceBattleLogicImpl>();
}
}
