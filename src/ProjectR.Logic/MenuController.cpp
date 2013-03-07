#include "MenuController.hpp"
#include "Menu.hpp"
#include "RInput.hpp"

namespace ProjectR
{
struct MenuControllerImpl : public MenuController
{
  void ControlMenu(std::shared_ptr<Menu> const& menu,
                   std::shared_ptr<RInput> const& input,
                   std::function<void()> const& cancelCallback)
  {
    input->Update();

    if(input->Action(Up))
      menu->Previous();
    else if(input->Action(Down))
      menu->Next();
    else if(input->Action(Cancel))
      cancelCallback();
    else if(input->Action(Confirm))
      menu->Run();
  }
};

std::shared_ptr<MenuController> MenuController::Create()
{
  return std::make_shared<MenuControllerImpl>();
}
}
