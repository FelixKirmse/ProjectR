#include "Observeable.hpp"
#include "IObserver.hpp"

namespace ProjectR
{
void Observeable::AddObserver(std::shared_ptr<IObserver> const& observer)
{
  _observers.push_back(observer);
}

void Observeable::NotifyObservers() const
{
  for(auto observer : _observers)
  {
    observer->Notify();
  }
}
}
