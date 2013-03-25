#include "LuaInterfaceFwd.hpp"
#include <memory>
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "Party.hpp"
#include "CharacterFactory.hpp"
#include "SpecialCharacter.hpp"
#include "RaceTemplates.hpp"

namespace ProjectR
{
static IModel const* Model = nullptr;

void SetModel(IModel const* model)
{
  if(Model == nullptr)
    Model = model;
}

void ForEachAttackerParty(char const* functionName)
{
  auto const& battleModel = Model->GetBattleModel();
  auto const& party = battleModel->AttackerIsEnemy() ? battleModel->GetEnemies() : battleModel->GetFrontRow();
  auto const& spell = std::static_pointer_cast<LuaSpell>(battleModel->GetTargetInfo().Spell);

  for(auto const& chara : party)
  {
    luabind::call_function<void>(spell->_spellState, functionName, boost::ref(*chara));
  }
}

void ForEachDefenderParty(char const* functionName)
{
  auto const& battleModel = Model->GetBattleModel();
  auto const& party = battleModel->AttackerIsEnemy() ? battleModel->GetFrontRow() : battleModel->GetEnemies();
  auto const& spell = std::static_pointer_cast<LuaSpell>(battleModel->GetTargetInfo().Spell);

  for(auto const& chara : party)
  {
    luabind::call_function<void>(spell->_spellState, functionName, boost::ref(*chara));
  }
}

void ForEachBackRow(char const* functionName)
{
  auto const& spell = std::static_pointer_cast<LuaSpell>(Model->GetBattleModel()->GetTargetInfo().Spell);
  for(auto const& chara : Model->GetParty()->GetBackSeat())
  {
    luabind::call_function<void>(spell->_spellState, functionName, boost::ref(*chara));
  }
}

bool IsSameChar(Character& char1, Character& char2)
{
  return &char1 == &char2;
}

int RollWrapper(int min, int max)
{
  return Roll(min, max);
}

Stats& GetStats(Character& character)
{
  return *character.GetStats();
}

int GetAliveCount()
{
  auto const& battleModel = Model->GetBattleModel();
  return battleModel->GetFrontRow().size() + battleModel->GetEnemies().size();
}

void BuffAttackersReserveParty(int stat, float amount)
{
  auto const& battleModel = Model->GetBattleModel();
  if(battleModel->AttackerIsEnemy())
    return;

  for(auto const& chara : Model->GetParty()->GetBackSeat())
  {
    chara->GetStats()->BuffStat(stat, amount);
  }
}

void ApplyDebuffWrapper(Character* character, int debuff, int strength)
{
  character->ApplyDebuff(debuff, strength);
}

int GetDeadMemberCountAttackerParty()
{
  auto const& battleModel = Model->GetBattleModel();
  return battleModel->AttackerIsEnemy() ? battleModel->GetDeadCountEnemy() : battleModel->GetDeadCountPlayer();
}

int GetDeadMemberCountDefenderParty()
{
  auto const& battleModel = Model->GetBattleModel();
  return battleModel->AttackerIsEnemy() ? battleModel->GetDeadCountPlayer() : battleModel->GetDeadCountEnemy();
}

void CreateMinion(std::shared_ptr<Character> const& minion)
{
  auto const& battleModel = Model->GetBattleModel();
  auto& minionVec = battleModel->AttackerIsEnemy() ? battleModel->GetEnemyMinions() : battleModel->GetPlayerMinions();
  auto const& specialChar = SpecialCharacter::CreateMinion(minion->GetName());
  specialChar->SetLore(minion->GetLore());
  specialChar->SetRace(minion->GetRace());
  specialChar->SetSpells(minion->GetSpells());
  specialChar->SetStats(minion->GetStats());
  specialChar->LvlUp(battleModel->GetCurrentAttacker()->GetLvl());
  minionVec.insert(minionVec.begin(), specialChar);
  if(minionVec.size() != 3)
    return;

  auto it = minionVec.end();
  --it;
  minionVec.erase(it);
}

void SummonNamedMinion(char const* name)
{
  CreateMinion(Model->GetCharacterFactory()->GetSpecialCharacter(name));
}

void SummonRandomMinion()
{
  CreateMinion(Model->GetCharacterFactory()->CreateRandomCharacter());
}

void SummonMinionOfSpecificRace(char const* race)
{
  CreateMinion(
        Model->GetCharacterFactory()->CreateRandomCharacter(
          1,
          &Model->GetRaceTemplates()->GetTemplate(race)));
}
}
