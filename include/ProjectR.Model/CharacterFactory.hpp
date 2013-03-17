#pragma once
#include <memory>
#include <vector>

namespace ProjectR
{
class Character;
class IModel;

class CharacterFactory
{
public:
  virtual void LoadCharacters() = 0;
  virtual std::vector<std::string> const& GetSpecialCharacterList() = 0;
  virtual std::shared_ptr<Character> CreateRandomCharacter() = 0;
  virtual std::shared_ptr<Character> const& GetSpecialCharacter(std::string const& name) = 0;

  virtual ~CharacterFactory(){}
  static std::shared_ptr<CharacterFactory> Create(IModel const& model);
};
}
