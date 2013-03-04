#pragma once
#include <memory>

namespace ProjectR
{
template<typename T>
class ISynchronizer;

template<typename T>
class ISynchronizeable
{
public:
  virtual void Sync(T value) = 0;
  virtual void SetSynchronizer(std::shared_ptr<ISynchronizer<T> > const& syncer) = 0;

  virtual ~ISynchronizeable() {}
};
}
