#pragma once
#include <memory>

namespace ProjectR
{
class IObserver;

class IObserveable
{
public:
  virtual void AddObserver(std::shared_ptr<IObserver> const& observer) = 0;
  virtual void NotifyObservers() const = 0;

  virtual ~IObserveable() {}
};
}
