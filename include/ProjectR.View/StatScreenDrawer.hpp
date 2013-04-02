#pragma once
#include "RConsole.hpp"
#include <memory>

namespace ProjectR
{
class Character;

class StatScreenDrawer : public RConsole
{
public:
  StatScreenDrawer(int x, int y) : RConsole(x,y){}
  virtual void DrawStats(std::shared_ptr<Character> const& chara,
                         RConsole* targetConsole = nullptr) = 0;
  virtual void SetPosition(int x, int y) = 0;

  virtual ~StatScreenDrawer(){}
  static std::shared_ptr<StatScreenDrawer> Create();
};
}
