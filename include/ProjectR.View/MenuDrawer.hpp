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
                        int row, int col, int offset = 0) = 0;

  virtual void DrawMenu(std::shared_ptr<Menu> const& menu,
                        RConsole* target,
                        int row = 0, int col = 0, int offset = 0) = 0;

  virtual void DrawMenu(std::shared_ptr<Menu> const& menu,
                        int row, int col, int offset,
                        RConsole* target) = 0;

  virtual ~MenuDrawer(){}
  static std::shared_ptr<MenuDrawer> Create();
};
}
