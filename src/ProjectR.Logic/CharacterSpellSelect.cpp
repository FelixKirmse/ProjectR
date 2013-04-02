#include "CharacterSpellSelect.hpp"
#include "Character.hpp"
#include "Stats.hpp"
#include "Spell.hpp"
#include "Extensions.hpp"
#include "BattleModel.hpp"

namespace ProjectR
{

std::shared_ptr<Character> getTarget(std::vector<std::shared_ptr<Character> > const& chars)
{
  /********************************
   * 60% to attack main tank      *
   * 30% to attack secondary tank *
   * 5% each to attack back row   *
   ********************************/
  std::shared_ptr<Character> target = nullptr;
  int size = chars.size();
  do
  {
    int targetRoll = Roll(99);
    target = chars[(targetRoll < 60) || size == 1 ?
          0 : (targetRoll < 90) || size == 2 ?
            1 : (targetRoll < 95) || size == 3 ?
              2 : 3];
  }while(target->IsDead());
  return target;
}


TargetInfo CharacterSpellSelect::SelectSpell(std::shared_ptr<Character> const& character,
                                             std::shared_ptr<BattleModel> const& battleModel,
                                             bool isEnemy)
{
  //TODO Check if Boss and has rotation
  TargetInfo targetInfo;
  bool lowHP = character->GetCurrentHP() / character->GetStats()->GetTotalStat(HP) <= .3f;
  bool lowMP = character->GetCurrentMP() <= 75.f;
  bool silenced = character->IsSilenced();
  bool defendAvailable = silenced || lowHP || lowMP;
  int spellSelectCount = 0;
  int initialSpellIndex = defendAvailable ? 1 : 2;
  auto spellList = character->GetSpells();

  do
  {
    ++spellSelectCount;
    if(spellSelectCount == 10)
      initialSpellIndex = 0;
    targetInfo.Spell = spellList[Roll(silenced ? 0 : initialSpellIndex, silenced ? 1 : spellList.size() - 1)];
  }
  while(targetInfo.Spell->GetMPCost(character) >= character->GetCurrentMP() + 1.f);

  targetInfo.Target = nullptr;

  TargetInfo::TargetType targetType = targetInfo.Spell->GetTargetType();
  if(targetType == TargetInfo::Allies || targetType == TargetInfo::Enemies)
    return targetInfo;

  if(targetType == TargetInfo::Myself)
  {
    targetInfo.Target = character;
    return targetInfo;
  }

  auto enemies = battleModel->GetEnemies();
  auto frontRow = battleModel->GetFrontRow();

  if(targetInfo.Spell->IsSupportSpell())
  {
    int rollMax = isEnemy ? enemies.size() - 1 : frontRow.size() - 1;
    do
    {
      targetInfo.Target = isEnemy ? enemies[Roll(rollMax)] : frontRow[Roll(rollMax)];
    }while(targetInfo.Target->IsDead());

    return targetInfo;
  }

  targetInfo.Target = isEnemy ? getTarget(frontRow) : getTarget(enemies);
  return targetInfo;
}
}
