#include "BattleModel.hpp"
#include "Stats.hpp"
#include "IModel.hpp"
#include "Extensions.hpp"
#include "CharacterFactory.hpp"
#include "BattleLog.hpp"
#include "Party.hpp"
#include "SpecialCharacter.hpp"

namespace ProjectR
{
struct BattleModelImpl : public BattleModel
{
  BattleModelImpl(IModel const* model)
    : _model(model)
  {
  }

  void SetTargetInfo(TargetInfo const& targetInfo)
  {
    _targetInfo = targetInfo;
  }

  TargetInfo& GetTargetInfo()
  {
    return _targetInfo;
  }

  std::vector<std::shared_ptr<Character> >& GetEnemies()
  {
    return _enemies;
  }

  std::vector<std::shared_ptr<Character> > const& GetFrontRow()
  {
    return *_frontRow;
  }

  std::vector<std::shared_ptr<Character> >& GetEnemyMinions()
  {
    return _enemyMinions;
  }

  std::vector<std::shared_ptr<Character> >& GetPlayerMinions()
  {
    return _playerMinions;
  }

  void SetCurrentAttacker(std::shared_ptr<Character> const& chara)
  {
    _currentAttacker = chara;
  }

  std::shared_ptr<Character> const& GetCurrentAttacker()
  {
    return _currentAttacker;
  }

  bool IsEnemyTurn()
  {
    return _isEnemyTurn;
  }

  void IsEnemyTurn(bool turn)
  {
    _isEnemyTurn = turn;
  }

  bool IsBossFight()
  {
    return _isBossFight;
  }

  BattleState GetCurrentState()
  {
    return _currentState;
  }

  void SetCurrentState(BattleState state)
  {
    _currentState = state;
  }

  void StartBattle(int level, std::string const& bossName)
  {
    _currentState = Idle;
    _level = level;
    _isBossFight = bossName != "";
    _enemies.clear();
    _enemyMinions.clear();
    _playerMinions.clear();
    _frontRow = &_model->GetParty()->GetFrontRow();
    _deadCountEnemy = 0;
    _deadCountParty = 0;
    _battleLog->ClearLog();
    GenerateEnemies(level, bossName);
    Character::SetTimeToAction(GetAvgSPD());
    SetInitialSpeed(_enemies);
    SetInitialSpeed(*_frontRow);
  }

  void GenerateEnemies(int level, std::string const& bossName)
  {
    if(_isBossFight)
    {
      auto boss = _model->GetCharacterFactory()->GetSpecialCharacter(bossName);
      boss->LvlUp(level);
      boss->GetStats()->GetSingleStat(HP)[Base] *= 25.f;
      _enemies.push_back(boss);
      //TODO Parse Bossfile of Boss, create Minions of him.
      return;
    }

    int enemyCount = Roll(3, 4);
    for(int i = 0; i < enemyCount; ++i)
    {
      _enemies.push_back(_model->GetCharacterFactory()->CreateRandomEnemy(level));
    }
  }

  void SetInitialSpeed(std::vector<std::shared_ptr<Character> > const& vec)
  {
    for(size_t i = 0; i < vec.size(); ++i)
    {
      vec[i]->SetTurnCounter(vec[i]->GetStats()->GetSingleStat(SPD)[Base]);
    }
  }

  float GetAvgSPD()
  {
    float spdTotal = 0.f;
    int charCount = 0;
    for(std::shared_ptr<Character> const& chara : _enemies)
    {
      spdTotal += chara->GetStats()->GetTotalStat(SPD);
      ++charCount;
    }

    for(std::shared_ptr<Character> const& chara : *_frontRow)
    {
      spdTotal += chara->GetStats()->GetTotalStat(SPD);
      ++charCount;
    }

    return spdTotal / charCount * 90.f;
  }

  bool TargetIsEnemy()
  {
    for(std::shared_ptr<Character> const& enemy : _enemies)
    {
      if(&(*enemy) == &(*_targetInfo.Target))
        return true;
    }
    return false;
  }

  bool AttackerIsEnemy()
  {
    for(std::shared_ptr<Character> const& enemy : _enemies)
    {
      if(&(*enemy) == &(*_currentAttacker))
        return true;
    }
    return false;
  }

  std::shared_ptr<BattleLog> const& GetBattleLog()
  {
    return _battleLog;
  }

  void RemoveEnemy(std::shared_ptr<Character> const& enemy)
  {
    auto const& it = std::find(_enemies.begin(), _enemies.end(), enemy);
    if(it == _enemies.end())
      return;

    _enemies.erase(it);
  }

  int GetDeadCountPlayer()
  {
    return _deadCountParty;
  }

  int GetDeadCountEnemy()
  {
    return _deadCountEnemy;
  }

  void EnemyDied()
  {
    ++_deadCountEnemy;
  }

  void PlayerDied()
  {
    ++_deadCountParty;
  }

  int GetBattleLvl()
  {
    return _level;
  }

  void SetExperienceEarned(int amount)
  {
    _xpEarned = amount;
  }

  int GetExperienceEarned()
  {
    return _xpEarned;
  }

  bool CharacterIsEnemy(std::shared_ptr<Character> const& chara)
  {
    for(auto const& enemy : _enemies)
    {
      if(chara == enemy)
        return true;
    }
    return false;
  }


  TargetInfo _targetInfo;
  std::vector<std::shared_ptr<Character> > _enemies;
  std::vector<std::shared_ptr<Character> > const* _frontRow;
  std::vector<std::shared_ptr<Character> > _enemyMinions;
  std::vector<std::shared_ptr<Character> > _playerMinions;
  std::shared_ptr<Character> _currentAttacker;
  BattleState _currentState = Idle;
  bool _isBossFight;
  IModel const* _model;
  bool _isEnemyTurn;
  std::shared_ptr<BattleLog> _battleLog = BattleLog::Create();
  int _deadCountEnemy = 0;
  int _deadCountParty = 0;
  int _level;
  int _xpEarned;
};

BattleModel* BattleModel::Create(IModel const* model)
{
  return new BattleModelImpl(model);
}
}
