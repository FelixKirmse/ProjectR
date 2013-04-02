#include "ActionSelect.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "MenuModel.hpp"
#include "ISpell.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"
#include "MenuController.hpp"
#include "Character.hpp"


namespace ProjectR
{
struct ActionSelectImpl : public ActionSelect, public Menu
{
  ActionSelectImpl()
  {
  }

  void Initialize()
  {
    _battleModel = Model()->GetBattleModel();
    _spell = MenuItem::Create("Spell", [&](){ Master()->SetCurrentState(SelectSpell); });
    _switch = MenuItem::Create("Switch", [&](){ Master()->SetCurrentState(Switch); });
    _convince = MenuItem::Create("Convince", [&](){ Master()->SetCurrentState(Convince); });
    _convince->Disabled(true);
    _controller = MenuController::Create();
    Model()->GetMenuModel()->SetBattleMenu(std::static_pointer_cast<Menu>(shared_from_this()));
    _initialized = true;
  }

  void Activate()
  {
    if(!_initialized)
      Initialize();

    _attack = MenuItem::Create(_battleModel->GetCurrentAttacker()->GetSpells().at(0)->GetName(),
                               [&](){ SetAttack(); });
    _defend = MenuItem::Create(_battleModel->GetCurrentAttacker()->GetSpells().at(1)->GetName(),
                               [&](){ SetDefend(); });

    ClearStates();
    AddState(_attack);
    AddState(_defend);
    AddState(_spell);
    AddState(_switch);
    AddState(_convince);
    SetCurrentState(0);
    _attack->Activate();
    Model()->CommitChanges();   
  }

  void SetAttack()
  {
    auto targetInfo = _battleModel->GetTargetInfo();
    targetInfo.Spell = _battleModel->GetCurrentAttacker()->GetSpells().at(0);
    _battleModel->SetTargetInfo(targetInfo);
    Master()->SetCurrentState(SelectTarget);
  }

  void SetDefend()
  {
    auto targetInfo = _battleModel->GetTargetInfo();
    targetInfo.Spell = _battleModel->GetCurrentAttacker()->GetSpells().at(1);
    _battleModel->SetTargetInfo(targetInfo);
    Master()->SetCurrentState(Execute);
  }

  void Run()
  {
    _controller->ControlMenu(std::static_pointer_cast<Menu>(shared_from_this()), Input(), [](){});
    Model()->CommitChanges();
  }

  bool _initialized = false;

  std::shared_ptr<MenuController> _controller;
  std::shared_ptr<BattleModel> _battleModel = nullptr;

  std::shared_ptr<MenuItem> _attack;
  std::shared_ptr<MenuItem> _defend;
  std::shared_ptr<MenuItem> _spell;
  std::shared_ptr<MenuItem> _switch;
  std::shared_ptr<MenuItem> _convince;
};

std::shared_ptr<ActionSelect> ActionSelect::Create()
{
  return std::make_shared<ActionSelectImpl>();
}
}
