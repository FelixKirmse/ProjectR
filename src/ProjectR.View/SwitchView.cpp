#include "SwitchView.hpp"
#include "IModel.hpp"
#include "Party.hpp"
#include "CharBattleFrame.hpp"
#include "RConsole.hpp"
#include "Initializeable.hpp"
#include "StatScreenDrawer.hpp"
#include "Character.hpp"
#include "MenuModel.hpp"
#include "SpellLister.hpp"

namespace ProjectR
{
struct SwitchViewImpl : public SwitchView, public Initializeable
{
  SwitchViewImpl()
    : _clearConsole(72, 22),
      _borderConsole(16, 10)
  {
    _drawer->SetPosition(80, 3);
    _lister->SetPosition(80, 43);
  }

  void Initialize()
  {
    _root = RConsole::GetRootConsole();
    for(int i = 0; i < 8; ++i)
    {
      int x = StartX + ColOffSet * (i % 4);
      int y = StartY + (i < 4 ? 0 : RowOffSet);

      _frames.push_back(CharBattleFrame::CreateFrameForPlayerChar());
      _frames.at(i)->SetPosition(x, y);
    }
  }

  void Run()
  {
    Init();

    _root->Blit(_clearConsole, _clearConsole.GetBounds(), 4, 4);

    _root->SetColourControl(TCOD_COLCTRL_1, Colour::red);
    _root->PrintString(4, 4, "%cReserve Party%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

    int deadCount = FrontRowSize - Model()->GetParty()->GetFrontRow().size();
    int selectedFrontRow = Model()->GetMenuModel()->GetSelectedSwitchIndex();

    for(int i = FrontRowSize - deadCount; i < FrontRowSize; ++i)
    {
      _borderConsole.SetForegroundColour(selectedFrontRow == i ? Colour::red : Colour::white);
      _borderConsole.DrawBorder();
      _root->Blit(_borderConsole, _borderConsole.GetBounds(), StartX + ColOffSet * i, 30);
    }

    auto const& backSeat = Model()->GetParty()->GetBackSeat();
    for(auto i = 0u; i < backSeat.size(); ++i)
    {
      _frames.at(i)->AssignCharacter(backSeat.at(i));
      _frames.at(i)->Draw();
    }

    std::shared_ptr<Character> selectedCharacter = nullptr;
    bool backRowSelected = false;
    for(auto const& chara : Model()->GetParty()->GetBackSeat())
    {
      if(chara->IsMarked())
      {
        backRowSelected = true;
        selectedCharacter = chara;
        break;
      }
    }

    if(!backRowSelected)
    {
      for(auto const& chara : Model()->GetParty()->GetFrontRow())
      {
        if(chara->IsMarked())
        {
          selectedCharacter = chara;
          break;
        }
      }
    }

    if(selectedCharacter != nullptr)
    {
      _drawer->DrawStats(selectedCharacter);
      _lister->Draw(selectedCharacter);
    }
  }

  RConsole* _root = nullptr;
  RConsole _clearConsole;
  RConsole _borderConsole;

  int const StartX = 7;
  int const StartY = 5;
  int const RowOffSet = 11;
  int const ColOffSet = 17;
  int const FrontRowSize = 4;

  std::vector<std::shared_ptr<CharBattleFrame> > _frames;
  std::shared_ptr<StatScreenDrawer> _drawer = StatScreenDrawer::Create();
  std::shared_ptr<SpellLister> _lister = SpellLister::Create();
};

std::shared_ptr<SwitchView> SwitchView::Create()
{
  return std::make_shared<SwitchViewImpl>();
}
}
