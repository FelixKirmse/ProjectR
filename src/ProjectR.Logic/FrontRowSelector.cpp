#include "FrontRowSelector.hpp"
#include "Initializeable.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "Character.hpp"
#include "RInput.hpp"
#include "StateMachine.hpp"
#include "MenuModel.hpp"

namespace ProjectR
{
struct FrontRowSelectorImpl : public FrontRowSelector, public Initializeable
{
  void Initialize()
  {
    _frontRow = &Model()->GetBattleModel()->GetFrontRow();
  }

  void Activate()
  {
     Init();
     if(_selectedIndex < (int)_frontRow->size())
       _frontRow->at(_selectedIndex)->IsMarked(false);
    _selectedIndex = 0;
    _frontRow->at(_selectedIndex)->IsMarked(true);
  }

  void Run()
  {
    int actualSize = _frontRow->size();
    if(_selectedIndex < actualSize)
      _frontRow->at(_selectedIndex)->IsMarked(true);

    Model()->CommitChanges();

    Input()->Update();
    if(Input()->Action(Left))
    {      
      if(_selectedIndex < actualSize)
        _frontRow->at(_selectedIndex)->IsMarked(false);

      _selectedIndex = _selectedIndex == 0 ? FrontRowSize - 1 : _selectedIndex - 1;
    }
    else if(Input()->Action(Right))
    {      
      if(_selectedIndex < actualSize)
        _frontRow->at(_selectedIndex)->IsMarked(false);

      _selectedIndex = _selectedIndex == FrontRowSize - 1 ? 0 : _selectedIndex + 1;
    }
    else if(Input()->Action(Cancel))
    {
      if(_selectedIndex < actualSize)
        _frontRow->at(_selectedIndex)->IsMarked(false);

      _selectedIndex = 0;
      Master()->Previous();
      return;
    }
    else if(Input()->Action(Confirm))
    {
      Master()->Next();
      return;
    }

    if(_selectedIndex < actualSize)
      _frontRow->at(_selectedIndex)->IsMarked(true);

    Model()->GetMenuModel()->SetSelectedSwitchIndex(_selectedIndex);
    Model()->CommitChanges();
  }

  std::vector<std::shared_ptr<Character> > const* _frontRow;
  int _selectedIndex = 0;
  int const FrontRowSize = 4;
};

std::shared_ptr<FrontRowSelector> FrontRowSelector::Create()
{
  return std::make_shared<FrontRowSelectorImpl>();
}
}
