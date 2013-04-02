#pragma once
#include <memory>

namespace ProjectR
{
class Character;

class CharBattleFrame
{
public:
  virtual void SetPosition(int x, int y) = 0;
  virtual void AssignCharacter(std::shared_ptr<Character> const& chara) = 0;
  virtual void Draw() = 0;

  virtual ~CharBattleFrame(){}
  static std::shared_ptr<CharBattleFrame> CreateFrameForPlayerChar();
  static std::shared_ptr<CharBattleFrame> CreateFrameForEnemyChar();
};
}
