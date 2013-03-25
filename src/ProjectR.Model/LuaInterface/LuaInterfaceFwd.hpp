#pragma once

namespace ProjectR
{
class Character;
class IModel;
class Stats;

void SetModel(IModel const* model);
void ForEachAttackerParty(char const* functionName);
void ForEachDefenderParty(char const* functionName);
void ForEachBackRow(char const* functionName);
bool IsSameChar(Character& char1, Character& char2);
int RollWrapper(int min, int max);
Stats& GetStats(Character& character);
int GetAliveCount();
void BuffAttackersReserveParty(int stat, float amount);
void ApplyDebuffWrapper(Character* character, int debuff, int strength);
int GetDeadMemberCountAttackerParty();
int GetDeadMemberCountDefenderParty();
void SummonNamedMinion(char const* name);
void SummonRandomMinion();
void SummonMinionOfSpecificRace(char const* race);
}
