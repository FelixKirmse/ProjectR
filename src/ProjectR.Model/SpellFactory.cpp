#include "SpellFactory.hpp"
#include "boost/unordered_map.hpp"
#include "Spell.hpp"
#include "Character.hpp"
#include "Stats.hpp"
#include <exception>
#include <luabind/luabind.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

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
      auto character = Character::Create("LuaTester");
      auto stats = Stats::GetRandomBaseStats();
      character->SetStats(stats);
      try
      {
        spell->DamageCalculation(character, character, 5.f);
      }
      catch(luabind::error& e)
      {
        std::cout << e.what() << std::endl;
        std::cout << "error: lua: " << luabind::object(luabind::from_stack(e.state(), -1)) << std::endl;
        exit(1);
      }
      _spells.push_back(spell);
      _stringIndexMap[spell->GetName()] = _spells.size() - 1;
    }
    exit(0);
  }

  std::shared_ptr<ISpell> const& GetSpell(std::string const& name)
  {
    return _spells[0];
  }

  std::shared_ptr<ISpell> const& GetRandomSpell()
  {
    return _spells[0];
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
