#pragma once
#include "TargetInfo.hpp"

namespace ProjectR
{
class ISpell
{
public:
  virtual void DamageCalculation(std::shared_ptr<Character> const& attacker,
                                 std::shared_ptr<Character> const& defender,
                                 float specialModifier = 1.f) = 0;
  virtual TargetInfo::TargetType GetTargetType() = 0;

  virtual std::string const& GetName() = 0;
  virtual std::string const& GetDescription() = 0;
  virtual float GetMPCost(std::shared_ptr<Character> const& caster) = 0;
  virtual bool IsSupportSpell() = 0;
  virtual void ForceReload() = 0;
  virtual float GetDelay() = 0;

  virtual ~ISpell(){}
};
}
