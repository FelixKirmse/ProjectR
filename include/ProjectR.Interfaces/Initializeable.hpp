#pragma once

namespace ProjectR
{
class Initializeable
{
public:
  virtual void Initialize() = 0;

  inline void Init()
  {
    if(_initialized)
      return;

    Initialize();
    _initialized = true;
  }

private:
  bool _initialized = false;
};
}
