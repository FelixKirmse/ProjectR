#include "CharacterFactory.hpp"
#include "IModel.hpp"
#include <boost/unordered_map.hpp>
#include <libtcod/libtcod.hpp>
#include "Stats.hpp"
#include <boost/filesystem.hpp>
#include "SpellFactory.hpp"
#include "RaceTemplates.hpp"
#include "ISpell.hpp"
#include <fstream>
#include "Extensions.hpp"
#include "SpecialCharacter.hpp"

namespace ProjectR
{
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
      _currentStats->SetSingleStat(stat, StatMapStringInt[propname]);
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

  std::shared_ptr<SpecialCharacter> CreateRandomEnemy(int level)
  {
    auto newChar = SpecialCharacter::CreateEnemy(GetRandomName());
    SharedGenerationFunction(newChar, level);
    return newChar;
  }

  std::shared_ptr<Character> CreateRandomCharacter(int level, RaceTemplate* race)
  {
    auto newChar = Character::Create(GetRandomName());
    SharedGenerationFunction(newChar, level, race);
    return newChar;
  }

  void SharedGenerationFunction(std::shared_ptr<Character>const & newChar, int level, RaceTemplate* race = 0)
  {
    auto const& rTemplate = race == nullptr ? _model.GetRaceTemplates()->GetRandomTemplate() :
                                              *race;
    auto randomStats = Stats::GetRandomBaseStats();
    randomStats->LvlUp(0, level);
    auto& spellFactory = _model.GetSpellFactory();
    newChar->SetRace(rTemplate.GetName());
    newChar->SetLore(rTemplate.GetDescription());
    ApplyRaceTemplate(rTemplate, randomStats);
    newChar->SetStats(randomStats);
    std::vector<std::shared_ptr<ISpell> > spells;
    spells.push_back(spellFactory->GetSpell("Attack"));
    spells.push_back(spellFactory->GetSpell("Defend"));
    int spellCount = Roll(2, 5);
    for(int i = 0; i < spellCount; ++i)
    {
      spells.push_back(spellFactory->GetRandomSpell());
    }
    newChar->SetSpells(spells);
  }

  void ApplyRaceTemplate(RaceTemplate const& tpl, std::shared_ptr<Stats> const& stats)
  {
    for(int i = HP; i <= SIL; ++i)
    {
      stats->GetSingleStat(i)[Base] *= tpl[i];
      stats->GetSingleStat(i)[Growth] *= tpl[i];
    }
  }

  std::string GetRandomName()
  {
    std::fstream nameFile("content/etc/Names.txt");
    GoToLine(nameFile, Roll(1, 13874));
    std::string name;
    std::getline(nameFile, name);
    return name;
  }

  void GoToLine(std::fstream& file, int line)
  {
    file.seekg(std::ios::beg);
    for(int i = 0; i < line - 1; ++i)
    {
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
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
