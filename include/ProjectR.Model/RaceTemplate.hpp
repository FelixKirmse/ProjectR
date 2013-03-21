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
  float operator[](int stat) const { return _mods[stat]; }
  void SetDescription(std::string const& description) { _description = description; }
  std::string const& GetDescription() const{ return _description; }
  void SetName(std::string const& name) { _name = name; }
  std::string const& GetName() const { return _name; }


private:
  float _mods[24];
  std::string _description;
  std::string _name;
};
}
