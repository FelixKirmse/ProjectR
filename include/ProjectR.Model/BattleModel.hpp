#pragma once
#include "TargetInfo.hpp"
#include <vector>
#include <string>

namespace ProjectR
{
class Character;
class Enemy;
class IModel;
class BattleLog;

enum BattleState
{
  Idle,
  BattleMenu,
  Consequences,
  GameOver,
  BattleWon
};

class BattleModel
{
public:
  virtual void SetTargetInfo(TargetInfo const& targetInfo) = 0;
  virtual TargetInfo& GetTargetInfo() = 0;

  virtual std::vector<std::shared_ptr<Character> >& GetEnemies() = 0;
  virtual std::vector<std::shared_ptr<Character> > const& GetFrontRow() = 0;
  virtual std::vector<std::shared_ptr<Character> >& GetEnemyMinions() = 0;
  virtual std::vector<std::shared_ptr<Character> >& GetPlayerMinions() = 0;
  virtual void RemoveEnemy(std::shared_ptr<Character> const& enemy) = 0;

  virtual std::shared_ptr<BattleLog> const& GetBattleLog() = 0;

  virtual void SetCurrentAttacker(std::shared_ptr<Character> const& chara) = 0;
  virtual std::shared_ptr<Character> const& GetCurrentAttacker() = 0;

  virtual bool IsEnemyTurn() = 0;
  virtual void IsEnemyTurn(bool turn) = 0;

  virtual bool IsBossFight() = 0;

  virtual BattleState GetCurrentState() = 0;
  virtual void SetCurrentState(BattleState state) = 0;

  virtual void StartBattle(int level, std::string const& bossName = std::string("")) = 0;
  virtual bool TargetIsEnemy() = 0;
  virtual bool AttackerIsEnemy() = 0;

  virtual int GetDeadCountPlayer() = 0;
  virtual int GetDeadCountEnemy() = 0;

  virtual void EnemyDied() = 0;
  virtual void PlayerDied() = 0;

  virtual int GetBattleLvl() = 0;
  virtual void SetExperienceEarned(int amount) = 0;
  virtual int GetExperienceEarned() = 0;

  virtual bool CharacterIsEnemy(std::shared_ptr<Character> const& chara) = 0;

  static BattleModel* Create(IModel const* model);
  ~BattleModel(){}
};
}
