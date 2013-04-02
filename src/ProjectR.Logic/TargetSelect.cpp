#include "IModel.hpp"
#include "TargetSelect.hpp"
#include "RInput.hpp"
#include "BattleModel.hpp"
#include "Character.hpp"
#include "ISpell.hpp"
#include "StateMachine.hpp"
#include "MenuModel.hpp"

namespace ProjectR
{
struct TargetSelectImpl : public TargetSelect
{
  void Initialize()
  {
    _battleModel = Model()->GetBattleModel();
    _initialized = true;
  }

  void Activate()
  {
    if(!_initialized)
      Initialize();

    _enemyRowSelected = !_battleModel->GetTargetInfo().Spell->IsSupportSpell();
    _activeRow = &(_enemyRowSelected ? _battleModel->GetEnemies() : _battleModel->GetFrontRow());
    _activeIndex = 0;
    _activeRow->at(_activeIndex)->IsMarked(true);
    _targetInfo = _battleModel->GetTargetInfo();
    _targetInfo.Target = _activeRow->at(_activeIndex);
    _battleModel->SetTargetInfo(_targetInfo);
  }

  void Run()
  {
    Model()->CommitChanges();
    _activeRow = &(_enemyRowSelected ? _battleModel->GetEnemies() : _battleModel->GetFrontRow());

    Input()->Update();
    if(Input()->Action(Up) || Input()->Action(Down))
    {
      _activeRow->at(_activeIndex)->IsMarked(false);
      _enemyRowSelected = !_enemyRowSelected;
      _activeRow = &(_enemyRowSelected ? _battleModel->GetEnemies() : _battleModel->GetFrontRow());
      _activeIndex = _activeIndex >= (int)_activeRow->size() ? _activeRow->size() - 1 : _activeIndex;
    }
    else if(Input()->Action(Left))
    {
      _activeRow->at(_activeIndex)->IsMarked(false);
      _activeIndex = _activeIndex == 0 ? _activeRow->size() - 1 : _activeIndex - 1;
    }
    else if(Input()->Action(Right))
    {
      _activeRow->at(_activeIndex)->IsMarked(false);
      _activeIndex = _activeIndex == (int)_activeRow->size() - 1 ? 0 : _activeIndex + 1;
    }
    else if(Input()->Action(Confirm))
    {
      _activeRow->at(_activeIndex)->IsMarked(false);
      Master()->SetCurrentState(Execute);
      _targetInfo.Target = _activeRow->at(_activeIndex);
      _battleModel->SetTargetInfo(_targetInfo);
      return;
    }
    else if(Input()->Action(Cancel))
    {
      Master()->SetCurrentState(SelectAction);
      _activeRow->at(_activeIndex)->IsMarked(false);
      Model()->CommitChanges();
      return;
    }

    _activeRow->at(_activeIndex)->IsMarked(true);
    _targetInfo.Target = _activeRow->at(_activeIndex);
    _battleModel->SetTargetInfo(_targetInfo);

    Model()->CommitChanges();
  }


  std::shared_ptr<BattleModel> _battleModel;
  std::vector<std::shared_ptr<Character> > const* _activeRow;
  int _activeIndex = 0;
  bool _initialized = false;
  bool _enemyRowSelected = true;
  TargetInfo _targetInfo;
};

std::shared_ptr<TargetSelect> TargetSelect::Create()
{
  return std::make_shared<TargetSelectImpl>();
}
}
