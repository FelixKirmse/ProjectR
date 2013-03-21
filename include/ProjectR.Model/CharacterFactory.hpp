#pragma once
#include <memory>
#include <vector>

namespace ProjectR
{
class Character;
class SpecialCharacter;
class IModel;
class RaceTemplate;

class CharacterFactory
{
public:
  virtual void LoadCharacters() = 0;
  virtual std::vector<std::string> const& GetSpecialCharacterList() = 0;
  virtual std::shared_ptr<Character> CreateRandomCharacter(int level = 1, RaceTemplate* race = nullptr) = 0;
  virtual std::shared_ptr<SpecialCharacter> CreateRandomEnemy(int level = 1) = 0;
  virtual std::shared_ptr<Character> const& GetSpecialCharacter(std::string const& name) = 0;

  virtual ~CharacterFactory(){}
  static std::shared_ptr<CharacterFactory> Create(IModel const& model);
};
}
