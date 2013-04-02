#include "Spell.hpp"
#include <string>
#include "Character.hpp"
#include "Stats.hpp"
#include "IModel.hpp"
#include "SpellFactory.hpp"
#include <lua5.1/lua.hpp>
#include <luabind/luabind.hpp>
#include "Extensions.hpp"
#include "ErrorCodes.hpp"
#include "LuaInterface/LuaInterfaceFwd.hpp"

namespace ProjectR
{
struct LuaSpell : public Spell
{
  LuaSpell(IModel const& model,
           std::string const& fileName)
    : _spellState(nullptr),
      _model(model),
      _fileName(fileName)
  {    
    SetModel(&model);
    ForceReload();    
  }

  void ForceReload()
  {
    try
    {
      if(_spellState != nullptr)
        lua_close(_spellState);

      _spellState = luaL_newstate();
      luabind::open(_spellState);
      luaL_dofile(_spellState, _fileName.c_str());
      BindStuffToLua();

      int target = luabind::call_function<int>(_spellState, "GetTargetType");
      _targetType = (TargetInfo::TargetType)target;
      _name = luabind::call_function<char const*>(_spellState, "GetName");
      _description = luabind::call_function<char const*>(_spellState, "GetDescription");
      _isSupportSpell = luabind::call_function<bool>(_spellState, "IsSupportSpell");
      _mpCost = luabind::call_function<float>(_spellState, "GetMPCost");
      _attackDelay = luabind::call_function<float>(_spellState, "GetDelay");
    }
    catch(luabind::error const& e)
    {
      std::cerr << e.what() << std::endl;
      std::cerr << luabind::object(luabind::from_stack(e.state(), -1)) << std::endl;
      exit(LUA_ERROR_RELOAD);
    }
    catch(...)
    {
      std::cerr << "Unknown Error at " << __LINE__ << " in " << __FILE__ << std::endl;
      exit(UNKNOWN_ERROR);
    }
  }

  float GetDelay()
  {
    return _attackDelay;
  }

  void BindStuffToLua()
  {
    try
    {
      luabind::globals(_spellState)["HP"] = 0;
      luabind::globals(_spellState)["MP"] = 1;
      luabind::globals(_spellState)["AD"] = 2;
      luabind::globals(_spellState)["MD"] = 3;
      luabind::globals(_spellState)["DEF"] = 4;
      luabind::globals(_spellState)["MR"] = 5;
      luabind::globals(_spellState)["EVA"] = 6;
      luabind::globals(_spellState)["SPD"] = 7;
      luabind::globals(_spellState)["CHA"] = 8;
      luabind::globals(_spellState)["FIR"] = 9;
      luabind::globals(_spellState)["WAT"] = 10;
      luabind::globals(_spellState)["ICE"] = 11;
      luabind::globals(_spellState)["ARC"] = 12;
      luabind::globals(_spellState)["WND"] = 13;
      luabind::globals(_spellState)["HOL"] = 14;
      luabind::globals(_spellState)["DRK"] = 15;
      luabind::globals(_spellState)["GRN"] = 16;
      luabind::globals(_spellState)["LGT"] = 17;
      luabind::globals(_spellState)["PSN"] = 18;
      luabind::globals(_spellState)["PAR"] = 19;
      luabind::globals(_spellState)["SLW"] = 20;
      luabind::globals(_spellState)["STD"] = 21;
      luabind::globals(_spellState)["DTH"] = 22;
      luabind::globals(_spellState)["SIL"] = 23;

      luabind::globals(_spellState)["Block"] = 0;
      luabind::globals(_spellState)["Dodge"] = 1;

      luabind::globals(_spellState)["Base"] = 0;
      luabind::globals(_spellState)["Item1"] = 1;
      luabind::globals(_spellState)["Item2"] = 2;
      luabind::globals(_spellState)["Item3"] = 3;
      luabind::globals(_spellState)["BattleMod"] = 4;
      luabind::globals(_spellState)["Growth"] = 5;
      luabind::globals(_spellState)["Multiplier"] = 6;

      luabind::globals(_spellState)["Single"] = 0;
      luabind::globals(_spellState)["Myself"] = 1;
      luabind::globals(_spellState)["Allies"] = 2;
      luabind::globals(_spellState)["Enemies"] = 3;
      luabind::globals(_spellState)["Decaying"] = 4;

      luabind::module(_spellState)
          [
          luabind::def("GetStats", GetStats),
          luabind::def("GetAliveCount", GetAliveCount),
          luabind::def("Roll", RollWrapper),
          luabind::def("BuffAttackersReserveParty", BuffAttackersReserveParty),
          luabind::def("ForEachAttackerParty", ForEachAttackerParty),
          luabind::def("ForEachDefenderParty", ForEachDefenderParty),
          luabind::def("ForEachBackRow", ForEachBackRow),
          luabind::def("IsSameChar", IsSameChar),
          luabind::def("GetDeadMemberCountAttackerParty", GetDeadMemberCountAttackerParty),
          luabind::def("GetDeadMemberCountDefenderParty", GetDeadMemberCountDefenderParty),
          luabind::def("SummonNamedMinion", SummonNamedMinion),
          luabind::def("SummonRandomMinion", SummonRandomMinion),
          luabind::def("SummonMinionOfSpecificRace", SummonMinionOfSpecificRace),
          luabind::def("GetTimeToAction", &Character::GetTimeToAction),
          luabind::class_<SingleStat>("SingleStat")
          .def("Get", &SingleStat::Get)
          .def("Set", &SingleStat::Set)
          ];

      luabind::module(_spellState)
          [
          luabind::class_<Stats>("Stats")
          .def("GetTotalStat", (float(Stats::*)(int))&Stats::GetTotalStat)
          .def("GetSingleStat", &Stats::GetSingleStat)
          .def("SetSingleStat", &Stats::SetSingleStat)          
          .def("RemoveBuffs", &Stats::RemoveBuffs)
          .def("RemoveDebuffs", &Stats::RemoveBuffs)
          .def("ReduceBuffeffectiveness", &Stats::ReduceBuffEffectiveness)
          ];

      luabind::module(_spellState)
          [
          luabind::class_<Character>("Character")
          .def("TakeDamage", &Character::TakeDamage)
          .def("TakeTrueDamage", &Character::TakeTrueDamage)
          .def("UseMP", &Character::UseMP)
          .def("Heal", &Character::Heal)
          .def("GetCurrentMP", &Character::GetCurrentMP)
          .def("GetCurrentHP", &Character::GetCurrentHP)
          .def("ApplyDebuff", &Character::ApplyDebuff)
          .def("ApplyDebuff", &ApplyDebuffWrapper)
          .def("GetLvl", &Character::GetLvl)
          .def("RemoveDebuffs", &Character::RemoveDebuffs)
          .def("SetTurnCounter", &Character::SetTurnCounter)
          .def("GetTurnCounter", &Character::GetTurnCounter)
          .def("BuffStat", &Character::BuffStat)
          ];
    }
    catch(luabind::error const& e)
    {
      std::cerr << e.what() << std::endl;
      std::cerr << luabind::object(luabind::from_stack(e.state(), -1)) << std::endl;
      exit(LUA_ERROR_BINDING);
    }
    catch(...)
    {
      std::cerr << "Unknown Error at " << __LINE__ << " in " << __FILE__ << std::endl;
      exit(UNKNOWN_ERROR);
    }
  }

  void AssignEssentials(std::shared_ptr<Character> const& attacker,
                         std::shared_ptr<Character> const& defender, float mod)
  {
    try
    {
      luabind::globals(_spellState)["a"] = boost::ref(*attacker);
      luabind::globals(_spellState)["d"] = boost::ref(*defender);
      luabind::globals(_spellState)["modifier"] = mod;

      luabind::globals(_spellState)["as"] = boost::ref(GetStats(*attacker));
      luabind::globals(_spellState)["ds"] = boost::ref(GetStats(*defender));
      auto as = attacker->GetStats();
      auto ds = defender->GetStats();

      luabind::globals(_spellState)["aHP"] = as->GetTotalStat(HP);
      luabind::globals(_spellState)["aMP"] = as->GetTotalStat(MP);
      luabind::globals(_spellState)["aAD"] = as->GetTotalStat(AD);
      luabind::globals(_spellState)["aMD"] = as->GetTotalStat(MD);
      luabind::globals(_spellState)["aDEF"] = as->GetTotalStat(DEF);
      luabind::globals(_spellState)["aMR"] = as->GetTotalStat(MR);
      luabind::globals(_spellState)["aEVA"] = as->GetTotalStat(EVA);
      luabind::globals(_spellState)["aSPD"] = as->GetTotalStat(SPD);
      luabind::globals(_spellState)["aCHA"] = as->GetTotalStat(CHA);
      luabind::globals(_spellState)["aFIR"] = as->GetTotalStat(FIR);
      luabind::globals(_spellState)["aWAT"] = as->GetTotalStat(WAT);
      luabind::globals(_spellState)["aICE"] = as->GetTotalStat(ICE);
      luabind::globals(_spellState)["aARC"] = as->GetTotalStat(ARC);
      luabind::globals(_spellState)["aWND"] = as->GetTotalStat(WND);
      luabind::globals(_spellState)["aHOL"] = as->GetTotalStat(HOL);
      luabind::globals(_spellState)["aDRK"] = as->GetTotalStat(DRK);
      luabind::globals(_spellState)["aGRN"] = as->GetTotalStat(GRN);
      luabind::globals(_spellState)["aLGT"] = as->GetTotalStat(LGT);
      luabind::globals(_spellState)["aPSN"] = as->GetTotalStat(PSN);
      luabind::globals(_spellState)["aPAR"] = as->GetTotalStat(PAR);
      luabind::globals(_spellState)["aSLW"] = as->GetTotalStat(SLW);
      luabind::globals(_spellState)["aSTD"] = as->GetTotalStat(STD);
      luabind::globals(_spellState)["aDTH"] = as->GetTotalStat(DTH);
      luabind::globals(_spellState)["aSIL"] = as->GetTotalStat(SIL);

      luabind::globals(_spellState)["dHP"] = ds->GetTotalStat(HP);
      luabind::globals(_spellState)["dMP"] = ds->GetTotalStat(MP);
      luabind::globals(_spellState)["dAD"] = ds->GetTotalStat(AD);
      luabind::globals(_spellState)["dMD"] = ds->GetTotalStat(MD);
      luabind::globals(_spellState)["dDEF"] = ds->GetTotalStat(DEF);
      luabind::globals(_spellState)["dMR"] = ds->GetTotalStat(MR);
      luabind::globals(_spellState)["dEVA"] = ds->GetTotalStat(EVA);
      luabind::globals(_spellState)["dSPD"] = ds->GetTotalStat(SPD);
      luabind::globals(_spellState)["dCHA"] = ds->GetTotalStat(CHA);
      luabind::globals(_spellState)["dFIR"] = ds->GetTotalStat(FIR);
      luabind::globals(_spellState)["dWAT"] = ds->GetTotalStat(WAT);
      luabind::globals(_spellState)["dICE"] = ds->GetTotalStat(ICE);
      luabind::globals(_spellState)["dARC"] = ds->GetTotalStat(ARC);
      luabind::globals(_spellState)["dWND"] = ds->GetTotalStat(WND);
      luabind::globals(_spellState)["dHOL"] = ds->GetTotalStat(HOL);
      luabind::globals(_spellState)["dDRK"] = ds->GetTotalStat(DRK);
      luabind::globals(_spellState)["dGRN"] = ds->GetTotalStat(GRN);
      luabind::globals(_spellState)["dLGT"] = ds->GetTotalStat(LGT);
      luabind::globals(_spellState)["dPSN"] = ds->GetTotalStat(PSN);
      luabind::globals(_spellState)["dPAR"] = ds->GetTotalStat(PAR);
      luabind::globals(_spellState)["dSLW"] = ds->GetTotalStat(SLW);
      luabind::globals(_spellState)["dSTD"] = ds->GetTotalStat(STD);
      luabind::globals(_spellState)["dDTH"] = ds->GetTotalStat(DTH);
      luabind::globals(_spellState)["dSIL"] = ds->GetTotalStat(SIL);
    }
    catch(luabind::error const& e)
    {
      std::cerr << e.what() << std::endl;
      std::cerr << luabind::object(luabind::from_stack(e.state(), -1)) << std::endl;
      exit(LUA_ERROR_ASSIGNING);
    }
    catch(...)
    {
      std::cerr << "Unknown Error at " << __LINE__ << " in " << __FILE__ << std::endl;
      exit(UNKNOWN_ERROR);
    }
  }

  void DamageCalculation(std::shared_ptr<Character> const& attacker,
                         std::shared_ptr<Character> const& defender,
                         float specialModifier)
  {
    try
    {
      AssignEssentials(attacker, defender, specialModifier);
      luabind::call_function<void>(_spellState, "SpellEffect");
      attacker->SetTurnCounter(_attackDelay * Character::GetTimeToAction());
    }
    catch(luabind::error const& e)
    {
      std::cerr << e.what() << std::endl;
      std::cerr << luabind::object(luabind::from_stack(e.state(), -1)) << std::endl;
      std::cerr << "Error with Spell " << _name << std::endl;
      exit(LUA_ERROR_CASTING);
    }
    catch(...)
    {
      std::cerr << "Unknown Error at " << __LINE__ << " in " << __FILE__ << std::endl;
      exit(UNKNOWN_ERROR);
    }
  }

  TargetInfo::TargetType GetTargetType()
  {
    return _targetType;
  }

  std::string const& GetName()
  {
    return _name;
  }

  std::string const& GetDescription()
  {
    return _description;
  }

  float GetMPCost(std::shared_ptr<Character> const& caster)
  {
    return 100.f * _mpCost;
  }

  bool IsSupportSpell()
  {
    return _isSupportSpell;
  }

  ~LuaSpell()
  {
    lua_close(_spellState);
  }

  lua_State* _spellState;
  IModel const& _model;
  TargetInfo::TargetType _targetType;
  std::string _name;
  std::string _description;
  bool _isSupportSpell;
  std::string const _fileName;
  float _mpCost;
  float _attackDelay;
};

std::shared_ptr<Spell> Spell::Create(IModel const& model,
                                     std::string const& fileName)
{
  return std::make_shared<LuaSpell>(model, fileName);
}
}
#include "LuaInterface/LuaInterfaceImpl.cc"
