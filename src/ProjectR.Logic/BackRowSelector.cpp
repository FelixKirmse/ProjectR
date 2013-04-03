#include "BackRowSelector.hpp"
#include "IModel.hpp"
#include "Party.hpp"
#include "StateMachine.hpp"
#include "Initializeable.hpp"
#include "Character.hpp"
#include "RInput.hpp"
#include "BattleModel.hpp"
#include "MenuModel.hpp"
#include "SpellFactory.hpp"

namespace ProjectR
{
struct BackRowSelectorImpl : public BackRowSelector, public Initializeable
{
  void Initialize()
  {
    _backRow = &Model()->GetParty()->GetBackSeat();
  }

  void Activate()
  {
    Init();

    _selectedIndex = 0;
    if(_backRow->size() == 0)
      return;
    _backRow->at(_selectedIndex)->IsMarked(true);
  }

  void Run()
  {
    Model()->CommitChanges();
    Input()->Update();

    if(Input()->Action(Down) || Input()->Action(Up))
    {
      if(_backRow->size() == 0)
        return;

      _backRow->at(_selectedIndex)->IsMarked(false);
      _selectedIndex =
          _selectedIndex > 3 ? _selectedIndex - 4 :
                               _selectedIndex + 4 < (int)_backRow->size() ? _selectedIndex + 4 :
                                                                            _backRow->size() - 1;
    }    
    else if(Input()->Action(Left))
    {
      if(_backRow->size() == 0)
        return;

      _backRow->at(_selectedIndex)->IsMarked(false);
      _selectedIndex = _selectedIndex == 0 ? _backRow->size() - 1 : _selectedIndex - 1;
    }
    else if(Input()->Action(Right))
    {
      if(_backRow->size() == 0)
        return;

      _backRow->at(_selectedIndex)->IsMarked(false);
      _selectedIndex = _selectedIndex == (int)_backRow->size() - 1 ? 0 : _selectedIndex + 1;
    }
    else if(Input()->Action(Cancel))
    {
      if(_backRow->size() != 0)
        _backRow->at(_selectedIndex)->IsMarked(false);

      _selectedIndex = 0;
      Master()->Previous();
      return;
    }
    else if(Input()->Action(Confirm))
    {
      if(_backRow->size() == 0)
        return;

      std::shared_ptr<Character> frontRowChar = nullptr;
      for(std::shared_ptr<Character> const& chara : Model()->GetParty()->GetFrontRow())
      {
        if(!chara->IsMarked())
          continue;

        frontRowChar = chara;
        chara->IsMarked(false);
        break;
      }

      _backRow->at(_selectedIndex)->IsMarked(false);
      TargetInfo targetInfo;
      targetInfo.Spell = Model()->GetSpellFactory()->GetSpell("Switch");
      targetInfo.Target = _backRow->at(_selectedIndex);
      Model()->GetBattleModel()->SetTargetInfo(targetInfo);

      Model()->GetParty()->SwitchCharacters(frontRowChar, _backRow->at(_selectedIndex));

      Model()->GetBattleModel()->SetCurrentState(Consequences);
      Model()->GetMenuModel()->SetBattleMenuState(SelectAction);      
      Model()->GetBattleModel()->GetCurrentAttacker()->SetTurnCounter(Character::GetTimeToAction() * .5f);
      Master()->Previous();
      Model()->GetParty()->GetFrontRow().at(0)->IsMarked(false);
      return;
    }

    if(_backRow->size() == 0)
      return;

    _backRow->at(_selectedIndex)->IsMarked(true);
    Model()->CommitChanges();
  }

  std::vector<std::shared_ptr<Character> > const* _backRow = nullptr;
  int _selectedIndex = 0;
};

std::shared_ptr<BackRowSelector> BackRowSelector::Create()
{
  return std::make_shared<BackRowSelectorImpl>();
}
}
