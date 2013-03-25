#pragma once
#include <memory>
#include <vector>

namespace ProjectR
{
class ISpell;
class Stats;

class Character
{
public:
  virtual std::string const& GetName() = 0;
  virtual std::vector<std::shared_ptr<ISpell> >const& GetSpells() = 0;
  virtual void SetSpells(std::vector<std::shared_ptr<ISpell> > const& _spells) = 0;
  virtual std::shared_ptr<Stats> const& GetStats() = 0;
  virtual void SetStats(std::shared_ptr<Stats> const& stats) = 0;
  virtual void SetRace(std::string const& race) = 0;
  virtual std::string const& GetRace() = 0;
  virtual std::string const& GetLore() = 0;
  virtual void SetLore(std::string const& lore) = 0;
  virtual void TakeDamage(float value) = 0;
  virtual void TakeTrueDamage(float value) = 0;
  virtual float GetCurrentHP() = 0;
  virtual float GetCurrentMP() = 0;
  virtual void UseMP(float value) = 0;
  virtual void Heal(float value) = 0;
  virtual void ApplyDebuff(int debuff, int strength, int level = 1) = 0;
  virtual int GetLvl() = 0;
  virtual void RemoveDebuffs() = 0;
  virtual float GetTurnCounter() = 0;
  virtual void SetTurnCounter(float newTurnCounter) = 0;
  static float GetTimeToAction();
  static void SetTimeToAction(float value);
  virtual void LvlUp(int levels = 1) = 0;
  virtual void LvlUp(long long experience) = 0;
  virtual bool IsDead() = 0;
  virtual bool UpdateTurnCounter() = 0;
  virtual bool IsSilenced() = 0;
  virtual void SetCurrentHP(float newValue) = 0;
  virtual void ResetDamageTaken() = 0;
  virtual float GetDamageTaken() = 0;
  virtual bool WasHealed() = 0;
  virtual bool BlockedDamage() = 0;
  virtual bool DodgedAttack() = 0;
  virtual bool WasAfflicted() = 0;
  virtual std::string const& AfflictedBy() = 0;
  virtual void BuffStat(int stat, float value) = 0;

  virtual std::shared_ptr<Character> Clone() = 0;
  virtual bool IsMinion() = 0;
  virtual void IsMinion(bool isMinion) = 0;

  virtual ~Character(){}
  static std::shared_ptr<Character> Create(std::string const& name);

protected:
  static float TimeToAction;
};
}
