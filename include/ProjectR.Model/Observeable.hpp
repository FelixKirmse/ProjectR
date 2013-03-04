#pragma once
#include "IObserveable.hpp"
#include "vector"

namespace ProjectR
{
class Observeable : public IObserveable
{
public:
  void AddObserver(std::shared_ptr<IObserver> const& observer);
  void NotifyObservers() const;

private:
  std::vector<std::shared_ptr<IObserver> > _observers;
};
}
