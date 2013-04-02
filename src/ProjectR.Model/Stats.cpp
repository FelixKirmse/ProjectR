#include "Stats.hpp"
#include "Extensions.hpp"

namespace ProjectR
{

struct StatsImpl : public Stats
{
  float GetTotalStat(int stat)
  {
    return stat <= CHA ? GetTotalStat((BaseStat)(stat)) :
                         stat <= LGT ? GetTotalStat((EleMastery)stat) :
                                       stat <= SIL ? GetTotalStat((DebuffResistance)stat) : 0.f;
  }

  float GetTotalStat(BaseStat stat)
  {
    SingleStat& s = _stats[stat];
    if(stat == HP || stat == MP)
      return s[Base] * (s[Multiplier] + s[Item1] + s[Item2] + s[Item3]);
    else
      return (s[Base] * (s[Multiplier] + s[Item1] + s[Item2] + s[Item3])) * s[BattleMod];
  }

  float GetTotalStat(EleMastery stat)
  {
    SingleStat& s = _stats[stat];
    return (s[Base] + s[Item1] + s[Item2] + s[Item3]) * s[BattleMod];
  }

  float GetTotalStat(DebuffResistance stat)
  {
    SingleStat& s = _stats[stat];
    return (s[Base] + s[Item1] + s[Item2] + s[Item3]) * s[BattleMod];
  }

  void SetSingleStat(SingleStat const& stat, int whichStat)
  {
    _stats[whichStat] = stat;
  }

  void LvlUp(int currentLevel, int amount)
  {
    int newLevel = currentLevel + amount;

    for(int l = 0; l < amount; ++l)
    {
      for(int i = 0; i < SPD; ++i)
      {
        if(i == MP)
          continue;
        SingleStat& stat = _stats[i];

        float const threshold = i == HP ? 6.66f : 5.f;
        float const growth = i == HP ? 0.03f : 0.02f;
        stat[Multiplier] += stat[Multiplier] < threshold ? growth : 0.f;
        stat[Base] += stat[Growth];
      }

      SingleStat& spd = _stats[SPD];
      spd[Multiplier] += 0.000645f;
      spd[Base] =  100.f + spd[Multiplier] * newLevel * spd[Growth];
    }

    _stats[MP][Base] =  200.f;
    _stats[MP][Multiplier] = 1.f;
  }

  float GetXPMultiplier() const
  {
    return _xpMultiplier;
  }

  void SetXPMultiplier(float xpMul)
  {
    _xpMultiplier = xpMul;
  }

  void BuffStat(int stat, float amount)
  {
    SingleStat& s = _stats[stat];
    s[BattleMod] += amount;
    float current = s[BattleMod];
    s[BattleMod] = current > 2.f ? 2.f : current < .5f ? .5f : current;
  }

  void ReduceBuffEffectiveness(int times)
  {
    for(int k = 0; k < times; ++k)
    {
      for(int i = 0; i < 24; ++i)
      {
        float& stat = _stats[i][BattleMod];
        if(stat < 1.f)
        {
          stat += .1f;
          stat = stat > 1.f ? 1.f : stat;
        }
        if(stat > 1.f)
        {
          stat -= .1f;
          stat = stat < 1.f ? 1.f : stat;
        }
      }
    }
  }

  void RemoveDebuffs()
  {
    for(int i = 0; i < 24; ++i)
    {
      float& stat = _stats[i][BattleMod];
      if(stat < 1.f)
        stat = 1.f;
    }
  }

  void RemoveBuffs()
  {
    for(int i = 0; i < 24; ++i)
    {
      float& stat = _stats[i][BattleMod];
      if(stat > 1.f)
        stat = 1.f;
    }
  }

  bool TryToApplyDebuff(DebuffResistance type, int successChance)
  {
    int resistance = GetTotalStat(type);
    return Roll(0, 99) < successChance - resistance;
  }

  float GetEVAChance(int level)
  {
    float stat = GetTotalStat(EVA);
    if(_evaType == Block)
      return stat;
    return stat / level;
  }

  EVAType GetEVAType()
  {
    return _evaType;
  }

  void SetEVAType(EVAType evaType)
  {
    _evaType = evaType;
  }

  SingleStat& GetSingleStat(int stat)
  {
    return _stats[stat];
  }

  std::shared_ptr<Stats> Clone()
  {
    std::shared_ptr<StatsImpl> const& clone = std::make_shared<StatsImpl>();
    clone->_evaType = _evaType;
    clone->_xpMultiplier = _xpMultiplier;
    for(int i = HP; i <= SIL; ++i)
      clone->_stats[i] = _stats[i];
    return clone;
  }

  SingleStat _stats[24];
  float _xpMultiplier = 1.f;
  EVAType _evaType;
};

std::shared_ptr<Stats> Stats::Create()
{
  return std::make_shared<StatsImpl>();
}

std::shared_ptr<Stats> Stats::GetRandomBaseStats()
{
  std::shared_ptr<StatsImpl> stats = std::make_shared<StatsImpl>();
  SingleStat& hp = stats->_stats[HP];
  hp[Base] = Roll(75, 200);
  hp[Growth] = Roll(5, 25);

  stats->_stats[MP][Base] = 200.f;

  for(int i = AD; i <= CHA; ++i)
  {
    SingleStat& s = stats->_stats[i];
    s[Base] = Roll(20, 80);
    s[Growth] = Roll(1, 20);
  }

  stats->_evaType = Roll(0, 99) < 10 ? Block : Dodge;

  if(stats->_evaType == Dodge)
  {
    stats->_stats[EVA][Base] = 2.0f;
    stats->_stats[EVA][Growth] = Roll(1, 8);
  }
  else
  {
    stats->_stats[EVA][Base] = Roll(20, 80);
    stats->_stats[EVA][Growth] = Roll(0, 1);
  }

  SingleStat& spd = stats->_stats[SPD];
  spd[Base] = 100.f;
  spd[Growth] = Roll(5, 15);
  spd[Multiplier] = 0.0225f;

  for(int i = FIR; i <= LGT; ++i)
  {
    stats->_stats[i][Base] = Roll(50, 200);
  }

  for(int i = PSN; i <= SIL; ++i)
  {
    stats->_stats[i][Base] = Roll(0, 30);
  }

  stats->_xpMultiplier = Roll(70, 140) / 100.f;
  return stats;
}
}
