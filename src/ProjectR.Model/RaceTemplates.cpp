#include "RaceTemplates.hpp"
#include <boost/unordered_map.hpp>
#include "libtcod/libtcod.hpp"
#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>
#include "ErrorCodes.hpp"
#include "Extensions.hpp"
#include "Stats.hpp"

namespace ProjectR
{
struct RaceTemplatesImpl : public RaceTemplates, public ITCODParserListener
{
  std::string const RacePath = "content/scripts/races/";

  void LoadTemplates()
  {
    using namespace boost::filesystem;
    TCODParser parser;
    DefineStructure(parser.newStructure("race"));
    path scriptDir(RacePath);
    directory_iterator end;
    for(directory_iterator i(scriptDir); i != end; ++i)
    {
      if(is_directory(i->path()) || i->path().extension() != ".cfg")
        continue;
      parser.run(i->path().c_str(), this);
    }
  }

  void DefineStructure(TCODParserStruct* def)
  {
    def->addProperty("description", TCOD_TYPE_STRING, true)
        ->addProperty("HP", TCOD_TYPE_FLOAT, false)
        ->addProperty("MP", TCOD_TYPE_FLOAT, false)
        ->addProperty("AD", TCOD_TYPE_FLOAT, false)
        ->addProperty("MD", TCOD_TYPE_FLOAT, false)
        ->addProperty("DEF", TCOD_TYPE_FLOAT, false)
        ->addProperty("MR", TCOD_TYPE_FLOAT, false)
        ->addProperty("EVA", TCOD_TYPE_FLOAT, false)
        ->addProperty("SPD", TCOD_TYPE_FLOAT, false)
        ->addProperty("CHA", TCOD_TYPE_FLOAT, false)
        ->addProperty("FIR", TCOD_TYPE_FLOAT, false)
        ->addProperty("WAT", TCOD_TYPE_FLOAT, false)
        ->addProperty("ICE", TCOD_TYPE_FLOAT, false)
        ->addProperty("ARC", TCOD_TYPE_FLOAT, false)
        ->addProperty("WND", TCOD_TYPE_FLOAT, false)
        ->addProperty("HOL", TCOD_TYPE_FLOAT, false)
        ->addProperty("DRK", TCOD_TYPE_FLOAT, false)
        ->addProperty("GRN", TCOD_TYPE_FLOAT, false)
        ->addProperty("LGT", TCOD_TYPE_FLOAT, false)
        ->addProperty("PSN", TCOD_TYPE_FLOAT, false)
        ->addProperty("PAR", TCOD_TYPE_FLOAT, false)
        ->addProperty("SLW", TCOD_TYPE_FLOAT, false)
        ->addProperty("DTH", TCOD_TYPE_FLOAT, false)
        ->addProperty("SIL", TCOD_TYPE_FLOAT, false);
  }

  bool parserNewStruct(TCODParser* parser, TCODParserStruct const* str, char const* name)
  {
    _currentTemplate = RaceTemplate();
    _currentRace = name;
    _currentTemplate.SetName(name);
    return true;
  }

  bool parserFlag(TCODParser *parser, const char *name)
  {
    return true;
  }

  bool parserProperty(TCODParser *parser, const char *propname, TCOD_value_type_t type, TCOD_value_t value)
  {
    if(type == TCOD_TYPE_FLOAT)
      _currentTemplate[StatMapStringInt[propname]] = value.f;
    else
      _currentTemplate.SetDescription(value.s);
    return true;
  }

  bool parserEndStruct(TCODParser *parser, const TCODParserStruct *str, const char *name)
  {    
    _stringIndexMap[_currentRace] = _templates.size();
    _templates.push_back(_currentTemplate);
    return true;
  }

  void error(const char *msg)
  {
    throw msg;
  }

  RaceTemplate const& GetTemplate(std::string const& name)
  {
    if(_stringIndexMap.find(name) == _stringIndexMap.end())
      Exit(ERROR_TEMPLATE_NOT_FOUND, "Racetemplate not found: " + name);

    return _templates[_stringIndexMap[name]];
  }

  RaceTemplate const& GetRandomTemplate()
  {
    return _templates[Roll(0, _templates.size() - 1)];
  }

  std::vector<RaceTemplate> _templates;
  boost::unordered::unordered_map<std::string, int> _stringIndexMap;
  RaceTemplate _currentTemplate;
  std::string _currentRace;
};

std::shared_ptr<RaceTemplates> RaceTemplates::Create()
{
  return std::make_shared<RaceTemplatesImpl>();
}
}
