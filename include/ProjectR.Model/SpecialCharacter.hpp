#pragma once
#include "Character.hpp"

namespace ProjectR
{
class SpecialCharacter : public Character
{
public:
  virtual std::shared_ptr<Character> ConvertToNormalCharacter() = 0;
  virtual ~SpecialCharacter(){}

  static std::shared_ptr<SpecialCharacter> CreateEnemy(std::string const& name);
  static std::shared_ptr<SpecialCharacter> CreateBoss(std::string const& name);
  static std::shared_ptr<SpecialCharacter> CreateMinion(std::string const& name);
};
}
