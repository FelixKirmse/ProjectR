#include "BattleView.hpp"
#include "IModel.hpp"
#include "StateMachine.hpp"
#include "BattleModel.hpp"
#include "BattleWonView.hpp"
#include "CharBattleFrame.hpp"
#include "RConsole.hpp"
#include "BattleLogDrawer.hpp"
#include "BattleMenuView.hpp"

namespace ProjectR
{
struct CommonBattleView : public ModelState
{
  CommonBattleView()
    : _logDrawer(BattleLogDrawer::Create()),
      EnemyMinionStart(24, 5),
      EnemyStart(7, 16),
      FrontRowStart(7, 30),
      PartyMinionStart(24, 41),
      FrameOffset(17)
  {
    _logDrawer->SetPosition(80, 43);

    for(int i = 0; i < 4; ++i)
    {
      _frontRowFrames.push_back(CharBattleFrame::CreateFrameForPlayerChar());
      _frontRowFrames[i]->SetPosition(FrontRowStart.X + FrameOffset * i, FrontRowStart.Y);

      _enemyFrames.push_back(CharBattleFrame::CreateFrameForEnemyChar());
      _enemyFrames[i]->SetPosition(EnemyStart.X + FrameOffset * i, EnemyStart.Y);

      if(i > 2)
        continue;

      _partyMinionFrames.push_back(CharBattleFrame::CreateFrameForPlayerChar());
      _partyMinionFrames[i]->SetPosition(PartyMinionStart.X + FrameOffset * i, PartyMinionStart.Y);

      _enemyMinionFrames.push_back(CharBattleFrame::CreateFrameForEnemyChar());
      _enemyMinionFrames[i]->SetPosition(EnemyMinionStart.X + FrameOffset * i, EnemyMinionStart.Y);
    }
  }

  void DrawBorders()
  {
    RConsole enemyBorder(74, 24);
    enemyBorder.DrawBorder();
    enemyBorder.SetColourControl(TCOD_COLCTRL_1, Colour::red);
    enemyBorder.PrintString(3, 5, "%cEnemy Party%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);

    RConsole* root = RConsole::GetRootConsole();
    root->Blit(enemyBorder, enemyBorder.GetBounds(), 3, 3);

    RConsole playerBorder(74, 23);
    playerBorder.DrawBorder();
    playerBorder.SetColourControl(TCOD_COLCTRL_1, Colour::red);
    playerBorder.PrintString(2, 18, "%cPlayer Party%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    root->Blit(playerBorder, playerBorder.GetBounds(), 3, 28);
  }

  void Activate()
  {
    _battleModel = Model()->GetBattleModel();
    _frontRow = &_battleModel->GetFrontRow();
    _enemies = &_battleModel->GetEnemies();
    _partyMinions = &_battleModel->GetPlayerMinions();
    _enemyMinions = &_battleModel->GetEnemyMinions();
    _logDrawer->Activate();
  }

  void Run()
  {
    DrawBorders();

    for(auto i = 0u; i < _frontRow->size(); ++i)
    {
      _frontRowFrames[i]->AssignCharacter((*_frontRow)[i]);
      _frontRowFrames[i]->Draw();
    }

    for(auto i = 0u; i < _partyMinions->size(); ++i)
    {
      _partyMinionFrames[i]->AssignCharacter((*_partyMinions)[i]);
      _partyMinionFrames[i]->Draw();
    }

    for(auto i = 0u; i < _enemies->size(); ++i)
    {
      _enemyFrames[i]->AssignCharacter((*_enemies)[i]);
      _enemyFrames[i]->Draw();
    }

    for(auto i = 0u; i < _enemyMinions->size(); ++i)
    {
      _enemyMinionFrames[i]->AssignCharacter((*_enemyMinions)[i]);
      _enemyMinionFrames[i]->Draw();
    }

    _logDrawer->Run();
  }

  std::shared_ptr<BattleModel> _battleModel;
  std::vector<std::shared_ptr<Character> > const* _frontRow;
  std::vector<std::shared_ptr<Character> > const* _partyMinions;
  std::vector<std::shared_ptr<Character> > const* _enemies;
  std::vector<std::shared_ptr<Character> > const* _enemyMinions;

  std::vector<std::shared_ptr<CharBattleFrame> > _frontRowFrames;
  std::vector<std::shared_ptr<CharBattleFrame> > _partyMinionFrames;
  std::vector<std::shared_ptr<CharBattleFrame> > _enemyFrames;
  std::vector<std::shared_ptr<CharBattleFrame> > _enemyMinionFrames;

  std::shared_ptr<BattleLogDrawer> const _logDrawer;

  Point const EnemyMinionStart;
  Point const EnemyStart;

  Point const FrontRowStart;
  Point const PartyMinionStart;

  int const FrameOffset;
};

struct BattleViewImpl : public BattleView, public StateMachine
{
  BattleViewImpl()
  {
  }

  void Initialize()
  {
    AddState(nullptr);
    AddState(BattleMenuView::Create());
    AddState(/*Consequences*/nullptr);
    AddState(/*GameOver*/nullptr);
    AddState(/*BattleWon*/BattleWonView::Create());
    SetCurrentState(0);
    _initialized = true;
    _common.Activate();
  }

  void Run()
  {
    if(!_initialized)
      Initialize();   

    _common.Run();

    auto const& currentState = GetState(Model()->GetBattleModel()->GetCurrentState());
    if(currentState != nullptr)
      currentState->Run();
  }

  CommonBattleView _common;
  bool _initialized = false;
};

std::shared_ptr<BattleView> BattleView::Create()
{
  return std::make_shared<BattleViewImpl>();
}
}
