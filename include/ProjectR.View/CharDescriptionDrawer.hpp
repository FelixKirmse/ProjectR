#pragma once
#include "RConsole.hpp"
#include <memory>

namespace ProjectR
{
class Character;

class CharDescriptionDrawer : public RConsole
{
public:
  CharDescriptionDrawer(int x, int y) : RConsole(x, y){}
  virtual void SetPosition(int x, int y) = 0;
  virtual void DrawSummary(std::shared_ptr<Character> const& chara, RConsole* target = nullptr) = 0;

  virtual ~CharDescriptionDrawer(){}
  static std::shared_ptr<CharDescriptionDrawer> Create();
};
}
