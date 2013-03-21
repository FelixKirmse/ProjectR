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
    BattlesFought,    // Taken Care Of by ConsequenceBattleLogic
    EnemiesKilled,    // Taken Care Of by ConsequenceBattleLogic
    EnemiesJoined,
    HighestPartyCount,
    SpellsCast,       // Taken Care Of by ConsequenceBattleLogic
    DamageDone,       // Taken Care Of by ConsequenceBattleLogic
    DamageTaken,      // Taken Care Of by ConsequenceBattleLogic
    HealingTaken,     // Taken Care Of by ConsequenceBattleLogic
    SuccessfulDodges, // Taken Care Of by ConsequenceBattleLogic
    DamageBlocked,    // Taken Care Of by ConsequenceBattleLogic
    PartyMembersLost, // Taken Care Of by ConsequenceBattleLogic
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
