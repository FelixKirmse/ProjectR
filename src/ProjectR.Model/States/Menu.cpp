#include "Menu.hpp"
#include "MenuItem.hpp"

namespace ProjectR
{
Menu::~Menu()
{
}

void Menu::Activate()
{
  SetCurrentState(0);
}

void Menu::Deactivate()
{
}

void Menu::Run()
{
}

void Menu::Next()
{
  int stateCount = GetStateCount();
  for(int i = 0; i < stateCount; ++i)
  {
    std::shared_ptr<MenuItem> menuItem = std::static_pointer_cast<MenuItem>(GetState(i));
    if(menuItem->IsSelected())
    {
      menuItem->Deactivate();
      SetCurrentState(i == stateCount - 1 ? 0: i + 1);
      std::shared_ptr<MenuItem> nextMenuItem = std::static_pointer_cast<MenuItem>(GetCurrentState());
      nextMenuItem->Activate();
      if(nextMenuItem->Disabled())
        Next();
      break;
    }
  }
}

void Menu::Previous()
{
  int stateCount = GetStateCount();
  for(int i = 0; i < stateCount; ++i)
  {
    std::shared_ptr<MenuItem> menuItem = std::static_pointer_cast<MenuItem>(GetState(i));
    if(menuItem->IsSelected())
    {
      menuItem->Deactivate();
      SetCurrentState(i == 0 ? stateCount - 1 : i - 1);
      std::shared_ptr<MenuItem> lastMenuItem = std::static_pointer_cast<MenuItem>(GetCurrentState());
      lastMenuItem->Activate();
      if(lastMenuItem->Disabled())
        Previous();
      break;
    }
  }
}

void Menu::SetStateMachine(std::shared_ptr<IStateMachine> const& machine)
{
}
}
