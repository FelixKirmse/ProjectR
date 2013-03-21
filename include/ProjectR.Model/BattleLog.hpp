#pragma once
#include <memory>
#include <vector>

namespace ProjectR
{
class Character;
class ISpell;

class BattleLog
{
public:
  virtual void LogAction(std::shared_ptr<Character> const& caster,
                         std::shared_ptr<Character> const& receiver,
                         std::shared_ptr<ISpell> const& spell) = 0; 
  virtual std::vector<std::string> GetLastEntries(int count) = 0;
  virtual void ClearLog() = 0;
  virtual std::vector<std::string> const& GetLog() = 0;

  static std::shared_ptr<BattleLog> Create();
  virtual ~BattleLog(){}
};
}
