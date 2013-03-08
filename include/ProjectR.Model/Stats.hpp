#pragma once
#include <memory>

namespace ProjectR
{
enum BaseStat
{
  HP = 0,     // Health Points
  MP = 1,     // Magic Points
  AD = 2,     // Attack Damage
  MD = 3,     // Magic Damage
  DEF = 4,    // Defense
  MR = 5,     // Magic Resist
  EVA = 6,    // Evasion Stat
  SPD = 7,    // Speed
  CHA = 8     // Charisma
};

enum EleMastery // increase damage done, decrease damage taken
{
  FIR = 9,     // Fire
  WAT = 10,    // Water
  ICE = 11,    // Ice
  ARC = 12,    // Arcane
  WND = 13,    // Wind
  HOL = 14,    // Holy
  DRK = 15,    // Dark
  GRN = 16,    // Ground
  LGT = 17     // Lightning
};

enum DebuffResistance
{
  PSN = 18,    // Poison
  PAR = 19,    // Paralyze
  SLW = 20,    // Slow -- OBSOLETE
  STD = 21,    // Statdrop -- OBSOLETE
  DTH = 22,    // Instant-Death
  SIL = 23     // Silence
};

enum EVAType
{
  Dodge,
  Block
};

/*
 * Each stat in the struct has 7 fields.
 * Stat[0] contains the base value of a stat
 * Stat[1] - Stat[3] contain the modifiers from items in the respective slot
 * Stat[4] contains temporary battle modifiers (buffs/debuffs)
 * Stat[5] contains the growth of a stat on levelup
 * Stat[6] contains the stat multiplier
 */
enum StatType
{
  Base,
  Item1,
  Item2,
  Item3,
  BattleMod,
  Growth,
  Multiplier
};
class SingleStat
{
public:
  float& operator[](StatType index) { return _statType[index]; }

private:
  float _statType[7] = {0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f};
};

class Stats
{
public:
  virtual float GetTotalStat(BaseStat stat) = 0;
  virtual float GetTotalStat(EleMastery stat) = 0;
  virtual float GetTotalStat(DebuffResistance stat) = 0;

  virtual SingleStat& GetSingleStat(int stat) = 0;

  virtual float GetXPMultiplier() const = 0;
  virtual void SetXPMultiplier(float xpMul) = 0;

  virtual void LvlUp(int currentLevel, int amount) = 0;

  virtual void BuffStat(int stat, float amount) = 0;

  virtual void ReduceBuffEffectiveness(int times = 1) = 0;
  virtual void RemoveBuffs() = 0;
  virtual void RemoveDebuffs() = 0;
  virtual bool TryToApplyDebuff(DebuffResistance type, int successChance) = 0;

  virtual EVAType GetEVAType() = 0;
  virtual void SetEVAType(EVAType evaType) = 0;

  virtual float GetEVAChance(int level) = 0;

  virtual ~Stats(){}
  static std::shared_ptr<Stats> Create();
  static std::shared_ptr<Stats> GetRandomBaseStats();
};
}
