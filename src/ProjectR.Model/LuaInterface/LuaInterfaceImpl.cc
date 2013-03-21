#include "LuaInterfaceFwd.hpp"
#include <memory>
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "Party.hpp"

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
}
