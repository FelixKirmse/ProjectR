#pragma once
#include <memory>

namespace ProjectR
{
class IObserver
{
public:
  virtual void Notify() = 0;

  virtual ~IObserver() {}
};
}
