#pragma once
#include <memory>

namespace ProjectR
{
template<typename T>
class ISynchronizeable;

template<typename T>
class ISynchronizer
{
public:
  virtual void Sync(T value) = 0;
  virtual void AddSynchronizeable(std::shared_ptr<ISynchronizeable<T> > sync) = 0;
  virtual void ClearSynchronizeables() = 0;

  virtual ~ISynchronizer() {}
};
}
