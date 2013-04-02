#include "Extensions.hpp"
#include "SpecialCharacter.hpp"
#include "Stats.hpp"
#include <string>
#include "boost/format.hpp"

namespace ProjectR
{
static unsigned long const XPRequiredForLvlUp = 2000UL;

struct CharacterImpl : public SpecialCharacter
{
  CharacterImpl(std::string const& name)
    : _name(name)
  {
  }

  bool IsMinion()
  {
    return _isMinion;
  }

  void IsMinion(bool isMinion)
  {
    _isMinion = isMinion;
  }

  virtual std::shared_ptr<Character> ConvertToNormalCharacter()
  {
    auto newChar = Character::Create(_name);
    newChar->SetSpells(_spells);
    newChar->SetLore(_lore);
    newChar->SetRace(_race);
    newChar->SetStats(_stats);
    newChar->SetTurnCounter(_turnCounter);
    return newChar;
  }

  void SetCurrentHP(float newValue)
  {
    _currentHP = newValue;
  }

  std::string const& GetName()
  {
    return _name;
  }

  std::string const& GetRace()
  {
    return _race;
  }

  void SetRace(std::string const& race)
  {
    _race = race;
  }

  virtual void SetStats(std::shared_ptr<Stats> const& stats)
  {
    _stats = stats;
    _currentHP = _stats->GetTotalStat(HP);
    _currentMP = _stats->GetTotalStat(MP);
    _xpRequired = _stats->GetXPMultiplier() * XPRequiredForLvlUp;
  }

  std::shared_ptr<Stats> const& GetStats()
  {
    return _stats;
  }

  std::vector<std::shared_ptr<ISpell> > const& GetSpells()
  {
    return _spells;
  }

  void SetSpells(std::vector<std::shared_ptr<ISpell> > const& spells)
  {
    _spells = spells;
  }

  void SetLore(std::string const& lore)
  {
    _lore = lore;
  }

  std::string const& GetLore()
  {
    return _lore;
  }

  void TakeDamage(float value)
  {
    if(value < 0.f)
      value = 0.f;
    bool attackEvaded = Roll(0,99) < _stats->GetEVAChance(_currentLevel);
    if(attackEvaded && _stats->GetEVAType() == Dodge)
    {
      _attackedDodged = true;
      return;
    }
    _attackBlocked = attackEvaded;
    value /= attackEvaded ? 2.f : 1.f;
    TakeTrueDamage(value);
  }

  void TakeTrueDamage(float value)
  {
    _damageTaken += value;
    _currentHP -= value;
    _currentHP = (_currentHP  < 0.f) ? 0.f : _currentHP;
  }

  bool IsDead()
  {
    return _currentHP <= 0.f;
  }

  float GetCurrentHP()
  {
    return _currentHP;
  }

  float GetCurrentMP()
  {
    return _currentMP;
  }

  void UseMP(float value)
  {
    _currentMP -= value;
    _currentMP =
        (_currentMP < 0.f) ? 0.f :
                             _currentMP > 200.f ?
                               200.f : _currentMP;
  }

  void RemoveDebuffs()
  {
  }

  void Heal(float value)
  {
    _healed = true;
    _damageTaken += value;
    _currentHP += value;
    _currentHP = (_currentHP > _stats->GetTotalStat(HP)) ?
          _stats->GetTotalStat(HP) : _currentHP;
  }

  void ApplyDebuff(int debuff, int strength, int level)
  {
    if(_stats->TryToApplyDebuff((DebuffResistance)debuff, strength))
      return;
  }

  int GetLvl()
  {
    return _currentLevel;
  }

  void LvlUp(int levels)
  {
    _stats->LvlUp(_currentLevel, levels);
    _currentLevel += levels;
    _currentHP = _stats->GetTotalStat(HP);
    _currentMP = _stats->GetTotalStat(MP);
  }

  void LvlUp(long long experience)
  {
    if(IsDead())
      return;

    long long currentLevelXP = _currentLevel * _xpRequired;
    long long difference = experience - currentLevelXP;

    while(difference > _xpRequired)
    {
      _stats->LvlUp(_currentLevel, 1);
      ++_currentLevel;
      difference -= _xpRequired;
    }

    Heal(_stats->GetTotalStat(HP));
    ResetDamageTaken();
  }

  void SetTurnCounter(float newTurnCounter)
  {
    _turnCounter = newTurnCounter;
  }

  float GetTurnCounter()
  {
    return _turnCounter;
  }

  bool UpdateTurnCounter()
  {
    if(IsDead())
      return false;

    float timeStep = _stats->GetTotalStat(SPD);
    // OnTurnCounterUpdate()

    bool result = false;
    _turnCounter += timeStep;

    if(_turnCounter >= TimeToAction)
    {
      UseMP(-10.f);
      _turnCounter -= TimeToAction;
      result = true;
      _stats->ReduceBuffEffectiveness();
      // OnTurnCounterActive
    }

    // OnTurnCounterUpdated
    _myTurn = result;
    return result;
  }

  bool IsSilenced()
  {
    return false;
  }

  void ResetDamageTaken()
  {
    _damageTaken = 0.f;
    _healed = false;
    _attackBlocked = false;
    _attackedDodged = false;
    _afflictedBy = "";
  }

  float GetDamageTaken()
  {
    return _damageTaken;
  }

  bool WasHealed()
  {
    return _healed;
  }

  bool BlockedDamage()
  {
    return _attackBlocked;
  }

  bool DodgedAttack()
  {
    return _attackedDodged;
  }

  bool WasAfflicted()
  {
    return _afflictedBy != "";
  }

  std::string const& AfflictedBy()
  {
    return _afflictedBy;
  }

  void BuffStat(int stat, float value)
  {
    boost::format addFormat("%+d%%%%%s");
    addFormat
        % (value * 100.f)
        % StatMapIntString[stat];
    std::string add = addFormat.str();
    if(_afflictedBy == "")
      _afflictedBy = add;
    else
    _afflictedBy += std::string(", ") + add;
    _stats->BuffStat(stat, value);
  }

  std::shared_ptr<Character> Clone()
  {
    auto const& clone = Create(_name);
    clone->SetLore(_lore);
    clone->SetRace(_race);
    clone->SetSpells(_spells);
    clone->SetStats(_stats->Clone());
    return clone;
  }

  bool TakesTurn()
  {
    return _myTurn;
  }

  void TurnEnded()
  {
    _myTurn = false;
  }

  void IsMarked(bool isMarked)
  {
    _isMarked = isMarked;
  }

  bool IsMarked()
  {
    return _isMarked;
  }

  float _currentHP;
  float _currentMP;

  std::vector<std::shared_ptr<ISpell> > _spells;
  std::shared_ptr<Stats> _stats;
  std::string _race;
  std::string const _name;
  std::string _lore;
  int _currentLevel = 1;
  float _damageTaken = 0.f;
  bool _attackedDodged = false;
  bool _attackBlocked = false;
  bool _healed = false;
  float _turnCounter = 0.f;  
  std::string _afflictedBy = "";
  long long _xpRequired;
  bool _isMinion = false;
  bool _myTurn = false;
  bool _isMarked = false;
};

float Character::TimeToAction;

void Character::SetTimeToAction(float value)
{
  TimeToAction = value;
}

float Character::GetTimeToAction()
{
  return TimeToAction;
}

struct EnemyImpl : public CharacterImpl
{
  EnemyImpl(std::string const& name)
    : CharacterImpl(name)
  {
  }

  virtual float GetHPMod()
  {
    return 5.f;
  }

  virtual float GetBaseMod()
  {
    return .4f;
  }

  void SetStats(std::shared_ptr<Stats> const& stats_)
  {
    auto stats = stats_;
    stats->GetSingleStat(HP)[Base] *= GetHPMod();
    float baseMod = GetBaseMod();
    for(int i = AD; i < CHA; ++i)
    {
      stats->GetSingleStat(i)[Base] *= baseMod;
    }
    CharacterImpl::SetStats(stats);
  }

  std::shared_ptr<Character> ConvertToNormalCharacter()
  {
    auto newChar = Character::Create(GetName());
    newChar->SetSpells(GetSpells());
    newChar->SetLore(GetLore());
    newChar->SetRace(GetRace());
    newChar->SetTurnCounter(GetTurnCounter());

    auto stats = GetStats();
    stats->GetSingleStat(HP)[Base] /= GetHPMod();
    float baseMod = GetBaseMod();
    for(int i = AD; i < CHA; ++i)
    {
      stats->GetSingleStat(i)[Base] /= baseMod;
    }
    newChar->SetStats(stats);
    return newChar;
  }
};

struct BossImpl : public EnemyImpl
{
  BossImpl(std::string const& name)
    : EnemyImpl(name)
  {
  }

  float GetHPMod()
  {
    return 20.f;
  }

  float GetBaseMod()
  {
    return .6f;
  }
};

struct MinionImpl : public EnemyImpl
{
  MinionImpl(std::string const& name)
    : EnemyImpl(name)
  {
  }

  float GetHPMod()
  {
    return .3f;
  }

  float GetBaseMod()
  {
    return .2f;
  }
};

std::shared_ptr<Character> Character::Create(std::string const& name)
{
  return std::make_shared<CharacterImpl>(name);
}

std::shared_ptr<SpecialCharacter> SpecialCharacter::CreateEnemy(std::string const& name)
{
  return std::make_shared<EnemyImpl>(name);
}

std::shared_ptr<SpecialCharacter> SpecialCharacter::CreateBoss(std::string const& name)
{
  return std::make_shared<BossImpl>(name);
}

std::shared_ptr<SpecialCharacter> SpecialCharacter::CreateMinion(std::string const& name)
{
  return std::make_shared<MinionImpl>(name);
}
}
