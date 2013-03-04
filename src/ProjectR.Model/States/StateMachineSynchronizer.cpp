#include "StateMachineSynchronizer.hpp"
#include "ISynchronizeable.hpp"

namespace ProjectR
{
StateMachineSynchronizer::StateMachineSynchronizer() = default;

void StateMachineSynchronizer::Sync(int value)
{
  for(auto syncers : _synchronizeables)
  {
    syncers->Sync(value);
  }
}

void StateMachineSynchronizer::AddSynchronizeable(std::shared_ptr<ISynchronizeable<int> > const& sync)
{
  sync->SetSynchronizer(shared_from_this());
  _synchronizeables.push_back(sync);
}

void StateMachineSynchronizer::ClearSynchronizeables()
{
  _synchronizeables.clear();
}
}
