#include "Character.hpp"
#include "Stats.hpp"
#include <string>

namespace ProjectR
{
struct CharacterImpl : public Character
{
  CharacterImpl(std::string const& name)
    : _name(name)
  {
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

  void SetStats(std::shared_ptr<Stats> const& stats)
  {
    _stats = stats;
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
    _currentHP -= value;
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
  }

  void RemoveDebuffs()
  {
  }

  void Heal(float value)
  {
    _currentHP += value;
  }

  void ApplyDebuff(int debuff, int strength, int level)
  {
    if(_stats->TryToApplyDebuff((DebuffResistance)debuff, strength))
      return;
  }

  int GetLvl()
  {
    return 10;
  }

  void TakeTrueDamage(float value)
  {
    TakeDamage(value);
  }

  void SetTurnCounter(float newTurnCounter)
  {
  }

  float GetTurnCounter()
  {
    return 123.f;
  }

  float GetTimeToAction()
  {
    return 0.f;
  }

  float _currentHP = 300.f;
  float _currentMP = 200.f;

  std::vector<std::shared_ptr<ISpell> > _spells;
  std::shared_ptr<Stats> _stats;
  std::string _race;
  std::string const _name;
  std::string _lore;
};

std::shared_ptr<Character> Character::Create(std::string const& name)
{
  return std::make_shared<CharacterImpl>(name);
}
}
