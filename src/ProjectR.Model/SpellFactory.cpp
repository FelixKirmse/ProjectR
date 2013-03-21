#include "SpellFactory.hpp"
#include "boost/unordered_map.hpp"
#include "Spell.hpp"
#include "Character.hpp"
#include "Stats.hpp"
#include <boost/filesystem.hpp>
#include "Extensions.hpp"
#include <iostream>
#include "ErrorCodes.hpp"

namespace ProjectR
{
struct SpellFacImpl : public SpellFactory
{
  SpellFacImpl(IModel const& model)
    : _model(model)
  {
  }

  std::string const ScriptPath = "content/scripts/spells/";

  void LoadSpells()
  {
    using namespace boost::filesystem;
    path scriptDir(ScriptPath);
    directory_iterator end;
    for(directory_iterator i(scriptDir); i != end; ++i)
    {
      if(is_directory(i->path()) || i->path().extension() != ".lua")
        continue;

      auto spell = Spell::Create(_model, i->path().c_str());     
      _spells.push_back(spell);
      _stringIndexMap[spell->GetName()] = _spells.size() - 1;
    }    
  }

  std::shared_ptr<ISpell> const& GetSpell(std::string const& name)
  {
    if(_stringIndexMap.find(name) == _stringIndexMap.end())
      Exit(ERROR_SPELL_NOT_FOUND, "Spell not found:" + name);

    return _spells[_stringIndexMap[name]];
  }

  std::shared_ptr<ISpell> const& GetRandomSpell()
  {    
    auto const& spell = _spells[Roll(0, _spells.size() - 1)];
    if(spell->GetName() == "Attack" || spell->GetName() == "Defend" || spell->GetName() == "Switch")
      return GetRandomSpell();

    return spell;
  }

  std::vector<std::shared_ptr<ISpell> > _spells;
  boost::unordered::unordered_map<std::string, int> _stringIndexMap;

  IModel const& _model;
};

std::shared_ptr<SpellFactory> SpellFactory::Create(IModel const& model)
{
  return std::make_shared<SpellFacImpl>(model);
}
}
