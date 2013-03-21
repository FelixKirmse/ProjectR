#include "BattleLog.hpp"
#include "Character.hpp"
#include "ISpell.hpp"
#include <string>
#include <sstream>

namespace ProjectR
{
struct BattleLogImpl : public BattleLog
{
  void LogAction(std::shared_ptr<Character> const& caster,
                  std::shared_ptr<Character> const& receiver,
                  std::shared_ptr<ISpell> const& spell)
  {
    TargetInfo::TargetType targetType = spell->GetTargetType();
    float damageValue = receiver->GetDamageTaken();

    std::stringstream stream;
    stream << caster->GetName() << " uses " << spell->GetName() << " on ";

    stream << (targetType == TargetInfo::Myself ? "self" : receiver->GetName());
    if(receiver->DodgedAttack())
        stream << " but the attack was dodged";
    else
      stream << (receiver->WasHealed() ? " healing for " : " dealing ") << damageValue << (receiver->WasHealed() ? " healing" : " damage");

    if(receiver->BlockedDamage())
      stream << " (blocked)";

    if(!receiver->WasAfflicted())
    {
      stream << "!";
      _log.push_back(stream.str());
      return;
    }

    stream << " and inflicted " << receiver->AfflictedBy() << "!";

    _log.push_back(stream.str());

    if(!receiver->IsDead())
      return;

    stream.str("");
    stream.clear();

    stream << receiver->GetName() << " dies!";
    _log.push_back(stream.str());
  }

  void ClearLog()
  {
    _log.clear();
  }

  std::vector<std::string> GetLastEntries(int count)
  {
    std::vector<std::string> result;
    int counter = 0;
    for(auto it = _log.rbegin(); it != _log.rend() && counter <= count; ++it, ++counter)
    {
      result.insert(result.begin(), *it);
    }
    return result;
  }

  std::vector<std::string> const& GetLog()
  {
    return _log;
  } 

  std::vector<std::string> _log;
};

std::shared_ptr<BattleLog> BattleLog::Create()
{
  return std::make_shared<BattleLogImpl>();
}
}
