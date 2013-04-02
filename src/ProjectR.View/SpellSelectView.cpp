#include "SpellSelectView.hpp"
#include "MenuDrawer.hpp"
#include "IModel.hpp"
#include "SpellFactory.hpp"
#include "MenuModel.hpp"
#include "RConsole.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"
#include "ISpell.hpp"
#include <boost/format.hpp>
#include "BattleModel.hpp"
#include "SpellDescriptionDrawer.hpp"

namespace ProjectR
{
struct SpellSelectViewImpl : public SpellSelectView, public RConsole
{
  SpellSelectViewImpl()
    : RConsole(55, 12)
  {
    _spellDrawer->SetPosition(80, 43);
  }

  void Run()
  {
    auto const& menu = Model()->GetMenuModel()->GetSpellSelectMenu();

    Clear();
    PrintString(0, 0, "Spell select:");
    PrintString(39, 0, "Cost:  Delay:");

    _drawer->DrawMenu(menu, this, 3, 2, 1);

    SetColourControl(TCOD_COLCTRL_1, Colour::red);
    SetColourControl(TCOD_COLCTRL_2, Colour::white);
    SetColourControl(TCOD_COLCTRL_3, Colour::grey);

    for(int i = 0; i < menu->GetStateCount(); ++ i)
    {
      auto const& item = std::static_pointer_cast<MenuItem>(menu->GetState(i));
      auto const& spell = Model()->GetSpellFactory()->GetSpell(item->GetLabel());
      PrintString(CostX, StartY + OffSetY * i,
                  (boost::format(CostFormat) % (int)spell->GetMPCost(Model()->GetBattleModel()->GetCurrentAttacker())).str(),
                  TCOD_RIGHT,
                  item->IsSelected() ? TCOD_COLCTRL_1 : item->Disabled() ? TCOD_COLCTRL_3 : TCOD_COLCTRL_2,
                  TCOD_COLCTRL_STOP);
      PrintString(DelayX, StartY + OffSetY * i,
                  (boost::format(DelayFormat) % int(100 - spell->GetDelay() * 100.f)).str(),
                  TCOD_RIGHT,
                  item->IsSelected() ? TCOD_COLCTRL_1 : item->Disabled() ? TCOD_COLCTRL_3 : TCOD_COLCTRL_2,
                  TCOD_COLCTRL_STOP);
    }

    GetRootConsole()->Blit(*this, GetBounds(), 22, 52);
    auto const& item = std::static_pointer_cast<MenuItem>(menu->GetCurrentState());
    auto const& spell = Model()->GetSpellFactory()->GetSpell(item->GetLabel());
    _spellDrawer->DrawSpellDescription(spell);
  }

  std::shared_ptr<MenuDrawer> _drawer = MenuDrawer::Create();
  std::shared_ptr<SpellDescriptionDrawer> _spellDrawer = SpellDescriptionDrawer::Create();
  int const CostX = 44;
  int const DelayX = 51;
  int const StartY = 2;
  int const OffSetY = 2;
  char const* CostFormat = "%%c%i MP%%c";
  char const* DelayFormat = "%%c%i%%%%%%c";
};

std::shared_ptr<SpellSelectView> SpellSelectView::Create()
{
  return std::make_shared<SpellSelectViewImpl>();
}
}
