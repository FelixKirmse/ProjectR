#pragma once
#include <memory>

namespace ProjectR
{
class ISpell;
class IModel;

class SpellFactory
{
public:
  virtual void LoadSpells() = 0;
  virtual std::shared_ptr<ISpell> const& GetSpell(std::string const& name) = 0;
  virtual std::shared_ptr<ISpell> const& GetRandomSpell() = 0;

  virtual ~SpellFactory(){}
  static std::shared_ptr<SpellFactory> Create(IModel const& model);
};
}
