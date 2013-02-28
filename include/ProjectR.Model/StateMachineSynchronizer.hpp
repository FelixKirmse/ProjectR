#pragma once
#include <vector>
#include "ISynchronizer.hpp"

namespace ProjectR
{
class StateMachineSynchronizer : public ISynchronizer<int>
{
public:
  StateMachineSynchronizer();

  void Sync(int value);
  void AddSynchronizeable(std::shared_ptr<ISynchronizeable<int> > sync);
  void ClearSynchronizeables();

private:
  std::vector<std::shared_ptr<ISynchronizeable<int> > > _synchronizeables;
};
}
