#include "Statistics.hpp"

namespace ProjectR
{
struct StatisticsImpl : public Statistics
{
  void AddToStatistic(Statistic statistic, int value)
  {
    _statistics[statistic] += value;
  }

  std::uint64_t GetStatistic(Statistic statistic)
  {
    return _statistics[statistic];
  }

  void Reset()
  {
    for(int i = 0; i < StatisticCount; ++i)
    {
      _statistics[i] = 0ULL;
    }
  }

  std::uint64_t _statistics[StatisticCount];
};

std::shared_ptr<Statistics> Statistics::Create()
{
  return std::make_shared<StatisticsImpl>();
}
}
