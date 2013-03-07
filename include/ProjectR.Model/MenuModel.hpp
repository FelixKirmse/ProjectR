#pragma once
#include <memory>

namespace ProjectR
{
class Menu;

class MenuModel
{
public:
  MenuModel();

  std::shared_ptr<Menu> const& GetMainMenu();
  std::shared_ptr<Menu> const& GetOptionsMenu();
  std::shared_ptr<Menu> const& GetIngameMenu();
  std::shared_ptr<Menu> const& GetPartyMenu();
  std::shared_ptr<Menu> const& GetInventoryMenu();
  std::shared_ptr<Menu> const& GetCharSwitchMenu();
  std::shared_ptr<Menu> const& GetBattleMenu();
  std::shared_ptr<Menu> const& GetSpellSelectMenu();
  std::shared_ptr<Menu> const& GetTargetSelectMenu();
  std::shared_ptr<Menu> const& GetActiveMenu();
  void SetActiveMenu(std::shared_ptr<Menu> const& menu);

private:
  std::shared_ptr<Menu> _mainMenu;
  std::shared_ptr<Menu> _optionsMenu;
  std::shared_ptr<Menu> _ingameMenu;
  std::shared_ptr<Menu> _partyMenu;
  std::shared_ptr<Menu> _inventoryMenu;
  std::shared_ptr<Menu> _charSwitchMenu;
  std::shared_ptr<Menu> _battleMenu;
  std::shared_ptr<Menu> _spellSelectMenu;
  std::shared_ptr<Menu> _targetSelectMenu;
  std::shared_ptr<Menu> _activeMenu;
};
}
