#pragma once
#include <memory>
#include <functional>

namespace ProjectR
{
class Menu;
class RInput;

class MenuController
{
public:
  virtual void ControlMenu(std::shared_ptr<Menu> const& menu,
                           std::shared_ptr<RInput> const& input,
                           std::function<void ()> const& cancelCallback) = 0;
  virtual ~MenuController(){}
  static std::shared_ptr<MenuController> Create();
};
}
