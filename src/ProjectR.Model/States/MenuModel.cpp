#include "MenuModel.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"
#include "MainMenu.hpp"

namespace ProjectR
{
void SetupMainMenu(std::shared_ptr<Menu> const& menu)
{
  menu->AddState(MenuItem::Create("New Game"));
  menu->AddState(MenuItem::Create("Load Game"));
  menu->AddState(MenuItem::Create("Options"));
  menu->AddState(MenuItem::Create("Quit"));

  menu->GetState(NewGame)->Activate();
}

void MenuModel::SetActiveMenu(std::shared_ptr<Menu> const& menu)
{
  _activeMenu = menu;
}

void MenuModel::SetBattleMenu(std::shared_ptr<Menu> const& menu)
{
  _battleMenu = menu;
}

std::shared_ptr<Menu> const& MenuModel::GetActiveMenu()
{
  return _activeMenu;
}

int MenuModel::GetBattleMenuState()
{
  return _battleMenuState;
}

void MenuModel::SetBattleMenuState(int state)
{
  _battleMenuState = state;
}

MenuModel::MenuModel()
  : _mainMenu(new Menu()),
    _optionsMenu(new Menu()),
    _activeMenu(_mainMenu),
    _selectedSwitchIndex(0)
{
  SetupMainMenu(_mainMenu);
  SetupMainMenu(_optionsMenu);
  _optionsMenu->GetState(2)->Activate();
}

std::shared_ptr<Menu> const& MenuModel::GetMainMenu()
{
  return _mainMenu;
}

std::shared_ptr<Menu> const& MenuModel::GetOptionsMenu()
{
  return _optionsMenu;
}

std::shared_ptr<Menu> const& MenuModel::GetIngameMenu()
{
  return _ingameMenu;
}

std::shared_ptr<Menu> const& MenuModel::GetPartyMenu()
{
  return _partyMenu;
}

std::shared_ptr<Menu> const& MenuModel::GetInventoryMenu()
{
  return _inventoryMenu;
}

std::shared_ptr<Menu> const& MenuModel::GetCharSwitchMenu()
{
  return _charSwitchMenu;
}

std::shared_ptr<Menu> const& MenuModel::GetBattleMenu()
{
  return _battleMenu;
}

std::shared_ptr<Menu> const& MenuModel::GetSpellSelectMenu()
{
  return _spellSelectMenu;
}

void MenuModel::SetSpellSelectMenu(std::shared_ptr<Menu> const& menu)
{
  _spellSelectMenu = menu;
}

std::shared_ptr<Menu> const& MenuModel::GetTargetSelectMenu()
{
  return _targetSelectMenu;
}

int MenuModel::GetSelectedSwitchIndex()
{
  return _selectedSwitchIndex;
}

void MenuModel::SetSelectedSwitchIndex(int index)
{
  _selectedSwitchIndex = index;
}

}
