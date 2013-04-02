#include "SpellSelect.hpp"
#include "Menu.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "ISpell.hpp"
#include "Character.hpp"
#include "Stats.hpp"
#include "MenuController.hpp"
#include "MenuModel.hpp"
#include "MenuItem.hpp"

namespace ProjectR
{
struct SpellSelectImpl : public SpellSelect, public Menu
{
  void Initialize()
  {
    _initiliazed = true;
    _battleModel = Model()->GetBattleModel();
  }

  void Activate()
  {
    if(!_initiliazed)
      Initialize();

    SetCurrentState(0);
    _targetInfo = _battleModel->GetTargetInfo();
    ClearStates();

    int currentMP = _battleModel->GetCurrentAttacker()->GetCurrentMP();

    int i = 0;
    for(auto const& spell : _battleModel->GetCurrentAttacker()->GetSpells())
    {
      ++i;
      if(i == 1 || i == 2)
        continue;

      auto const item = MenuItem::Create(spell->GetName(),
                                         [&]()
      {
        _targetInfo.Spell = spell;
        _battleModel->SetTargetInfo(_targetInfo);
        if(spell->GetTargetType() == TargetInfo::Single || spell->GetTargetType() == TargetInfo::Decaying)
          Master()->SetCurrentState(SelectTarget);
        else
          Master()->SetCurrentState(Execute);
      });
      item->Disabled(spell->GetMPCost(_battleModel->GetCurrentAttacker()) > currentMP + 1);
      AddState(item);
    }

    Model()->GetMenuModel()->SetSpellSelectMenu(std::static_pointer_cast<Menu>(shared_from_this()));

    for(int i = 0; i < GetStateCount(); ++i)
    {
      std::shared_ptr<MenuItem> const& item = std::static_pointer_cast<MenuItem>(GetState(i));
      if(item->Disabled())
        continue;

      item->Activate();
      SetCurrentState(i);
      break;
    }
  }

  void Run()
  {
    _controller->ControlMenu(std::static_pointer_cast<Menu>(shared_from_this()),
                             Input(),
                             [&](){ Master()->SetCurrentState(SelectAction); });
  }

  bool _initiliazed = false;
  std::shared_ptr<BattleModel> _battleModel = nullptr;
  std::shared_ptr<MenuController> _controller = MenuController::Create();
  TargetInfo _targetInfo;
};

std::shared_ptr<SpellSelect> SpellSelect::Create()
{
  return std::make_shared<SpellSelectImpl>();
}
}
