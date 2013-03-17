#pragma once
#include "ISpell.hpp"

namespace ProjectR
{
class IModel;
class Spell : public ISpell
{
public:
  virtual ~Spell(){}
  static std::shared_ptr<Spell> Create(IModel const& model,
                                       std::string const& file);
};
}
