#pragma once
#include <memory>

namespace ProjectR
{
class Menu;
class RConsole;

class MenuDrawer
{
public:
  virtual void DrawMenu(std::shared_ptr<Menu> const& menu,
                        int row, int col,
                        RConsole* target = nullptr) = 0;

  virtual ~MenuDrawer(){}
  static std::shared_ptr<MenuDrawer> Create();
};
}
