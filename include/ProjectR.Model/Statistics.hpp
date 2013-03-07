#pragma once
#include <cstdint>
#include <memory>

namespace ProjectR
{
class Statistics
{
public:
  enum Statistic
  {
    StepsTaken,
    MapsGenerated,
    SquaresRevealed,
    BattlesFought,
    EnemiesKilled,
    EnemiesJoined,
    HighestPartyCount,
    SpellsCast,
    DamageDone,
    DamageTaken,
    HealingDone,
    HealingTaken,
    SuccessfulDodges,
    DamageBlocked,
    PartyMembersLost,
    KeysUsed,
    DoorsOpened,
    ChestsOpened,
    UncommonChestsFound,
    RareChestsFound,
    EpicChestsFound,
    LegendaryChestsFouns,
    ArtifactChestsFound,
    NormalChestsFound,
    SmallChestsFound,
    BigChestsFound,
    GrandChestsFound,
    GrandArtifactChestsFound,
    GrandArtifactChestsMissed,
    StatisticCount
  };

  virtual void AddToStatistic(Statistic statistic, int value) = 0;
  virtual std::uint64_t GetStatistic(Statistic statistic) = 0;
  virtual void Reset() = 0;

  ~Statistics(){}
  static std::shared_ptr<Statistics> Create();
};
}
