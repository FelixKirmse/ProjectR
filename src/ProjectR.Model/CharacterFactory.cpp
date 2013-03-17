#include "CharacterFactory.hpp"
#include "IModel.hpp"
#include "Character.hpp"
#include <boost/unordered_map.hpp>
#include <libtcod/libtcod.hpp>
#include "Stats.hpp"
#include <boost/filesystem.hpp>
#include "SpellFactory.hpp"

namespace ProjectR
{
static boost::unordered::unordered_map<std::string, int> _statMap =
{
  {"HP", 0},
  {"MP", 1},
  {"AD", 2},
  {"MD", 3},
  {"DEF", 4},
  {"MR", 5},
  {"EVA", 6},
  {"SPD", 7},
  {"CHA", 8},
  {"FIR", 9},
  {"WAT", 10},
  {"ICE", 11},
  {"ARC", 12},
  {"WND", 13},
  {"HOL", 14},
  {"DRK", 15},
  {"GRN", 16},
  {"LGT", 17},
  {"PSN", 18},
  {"PAR", 19},
  {"SLW", 20},
  {"STD", 21},
  {"DTH", 22},
  {"SIL", 23}
};

struct CharacterFacImpl : public CharacterFactory, public ITCODParserListener
{
  CharacterFacImpl(IModel const& model)
    : _model(model)
  {
  }

  std::string const ScriptPath = "content/scripts/characters/";

  void LoadCharacters()
  {
    using namespace boost::filesystem;
    _spellFactory = _model.GetSpellFactory();
    TCODParser parser;
    SetupParserStruct(parser.newStructure("character"));
    path scriptDir(ScriptPath);
    directory_iterator end;
    for(directory_iterator i(scriptDir); i != end; ++i)
    {
      if(is_directory(i->path()) || i->path().extension() != ".cfg")
        continue;
      parser.run(i->path().c_str(), this);
    }
  }

  void SetupParserStruct(TCODParserStruct* struc)
  {
    struc->addListProperty("HP", TCOD_TYPE_FLOAT, true)
        ->addListProperty("MP", TCOD_TYPE_FLOAT, true)
        ->addListProperty("AD", TCOD_TYPE_FLOAT, true)
        ->addListProperty("MD", TCOD_TYPE_FLOAT, true)
        ->addListProperty("DEF", TCOD_TYPE_FLOAT, true)
        ->addListProperty("MR", TCOD_TYPE_FLOAT, true)
        ->addListProperty("EVA", TCOD_TYPE_FLOAT, true)
        ->addListProperty("SPD", TCOD_TYPE_FLOAT, true)
        ->addListProperty("CHA", TCOD_TYPE_FLOAT, true)
        ->addProperty("FIR", TCOD_TYPE_FLOAT, true)
        ->addProperty("WAT", TCOD_TYPE_FLOAT, true)
        ->addProperty("ICE", TCOD_TYPE_FLOAT, true)
        ->addProperty("ARC", TCOD_TYPE_FLOAT, true)
        ->addProperty("WND", TCOD_TYPE_FLOAT, true)
        ->addProperty("HOL", TCOD_TYPE_FLOAT, true)
        ->addProperty("DRK", TCOD_TYPE_FLOAT, true)
        ->addProperty("GRN", TCOD_TYPE_FLOAT, true)
        ->addProperty("LGT", TCOD_TYPE_FLOAT, true)
        ->addProperty("PSN", TCOD_TYPE_FLOAT, true)
        ->addProperty("PAR", TCOD_TYPE_FLOAT, true)
        ->addProperty("SLW", TCOD_TYPE_FLOAT, false)
        ->addProperty("DTH", TCOD_TYPE_FLOAT, true)
        ->addProperty("SIL", TCOD_TYPE_FLOAT, true)
        ->addProperty("XP", TCOD_TYPE_FLOAT, true)
        ->addFlag("Block")
        ->addProperty("Race", TCOD_TYPE_STRING, false)
        ->addProperty("Attack", TCOD_TYPE_STRING, false)
        ->addProperty("Defend", TCOD_TYPE_STRING, false)
        ->addProperty("Description", TCOD_TYPE_STRING, true)
        ->addListProperty("Spells", TCOD_TYPE_STRING, true);
  }

  bool parserNewStruct(TCODParser* parser, TCODParserStruct const* str, char const* name)
  {
    _currentSpells.clear();
    _currentSpells.push_back(_spellFactory->GetSpell("Attack"));
    _currentSpells.push_back(_spellFactory->GetSpell("Defend"));
    _currentChar = Character::Create(name);
    _currentStats = Stats::Create();
    _currentStats->SetEVAType(Dodge);
    _currentChar->SetRace("Human");
    return true;
  }

  bool parserFlag(TCODParser *parser, const char *name)
  {
    if(name == std::string("Block"))
      _currentStats->SetEVAType(Block);
    return true;
  }

  bool parserProperty(TCODParser *parser, const char *propname, TCOD_value_type_t type, TCOD_value_t value)
  {
    if(propname == std::string("XP"))
    {
      _currentStats->SetXPMultiplier(value.f);
      return true;
    }

    if(propname == std::string("Description"))
    {
      _currentChar->SetLore(value.s);
      return true;
    }

    if(propname == std::string("Attack"))
    {
      _currentSpells[0] = _spellFactory->GetSpell(value.s);
      return true;
    }

    if(propname == std::string("Defend"))
    {
      _currentSpells[1] = _spellFactory->GetSpell(value.s);
      return true;
    }

    switch((int)type)
    {

    case TCOD_TYPE_STRING:
      _currentChar->SetRace(value.s);
      return true;

    case TCOD_TYPE_LIST | TCOD_TYPE_FLOAT:
    {
      SingleStat stat;

      TCODList<float> valueList(value.list);

      stat[Growth] = valueList.pop();
      stat[Base] = valueList.pop();
      _currentStats->SetSingleStat(stat, _statMap[propname]);
      return true;
    }

    case TCOD_TYPE_LIST | TCOD_TYPE_STRING:
    {
      TCODList<char*> spellList(value.list);
      for(auto it = spellList.begin(); it != spellList.end(); ++it)
      {
        _currentSpells.push_back(_spellFactory->GetSpell(*it));
      }
    }

    case TCOD_TYPE_FLOAT:
    {
      SingleStat stat;
      stat[Base] = value.f;
      return true;
    }

    default:
      return false;

    }
    return false;
  }

  bool parserEndStruct(TCODParser *parser, const TCODParserStruct *str, const char *name)
  {
    _currentChar->SetStats(_currentStats);
    _currentChar->SetSpells(_currentSpells);
    _specialChars[_currentChar->GetName()] = _currentChar;
    _specialCharList.push_back(_currentChar->GetName());
    return true;
  }

  void error(const char *msg)
  {
    throw msg;
  }

  std::shared_ptr<Character> CreateRandomCharacter()
  {
    return nullptr;
  }

  std::shared_ptr<Character> const& GetSpecialCharacter(std::string const& name)
  {
    return _specialChars[name];
  }

  std::vector<std::string> const& GetSpecialCharacterList()
  {
    return _specialCharList;
  }

  std::vector<std::string> _specialCharList;
  boost::unordered::unordered_map<std::string, std::shared_ptr<Character> > _specialChars;
  IModel const& _model;
  std::shared_ptr<Character> _currentChar;
  std::shared_ptr<Stats> _currentStats;
  std::shared_ptr<SpellFactory> _spellFactory;
  std::vector<std::shared_ptr<ISpell> > _currentSpells;
};

std::shared_ptr<CharacterFactory> CharacterFactory::Create(IModel const& model)
{
  return std::make_shared<CharacterFacImpl>(model);
}
}
