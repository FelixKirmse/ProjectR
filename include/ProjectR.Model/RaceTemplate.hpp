#pragma once
#include <algorithm>
#include <string>

namespace ProjectR
{
class RaceTemplate
{
public:
  RaceTemplate()
  {
    std::fill(_mods, _mods + 24, 1.f);
  }

  float& operator[](int stat){ return _mods[stat]; }
  void SetDescription(std::string const& description) { _description = description; }
  std::string const& GetDescription(){ return _description; }


private:
  float _mods[24];
  std::string _description;
};
}
