#include "ConsoleView.hpp"
#include "RConsole.hpp"
#include "TitleScreenView.hpp"
#include "MainMenuView.hpp"
#include "libtcod/libtcod.hpp"
#include "PreGameView.hpp"
#include "OverworldView.hpp"
#include "BattleView.hpp"

namespace ProjectR
{
struct ConsoleViewImpl : public ConsoleView
{
  ConsoleViewImpl()
    : _model()
  {
    RConsole::InitializeRootConsole(1920.f / 8 / 2, 1080.f / 8 / 2);
    TCODSystem::setFps(30);
    RConsole::GetRootConsole()->SetBackgroundColour(Colour::black);
    RConsole::GetRootConsole()->SetForegroundColour(Colour::white);
  }

  ~ConsoleViewImpl()
  {
  }

  void Show()
  {
    RunCurrentState();
    RConsole::Draw();
  }

  void Notify()
  {
    Show();
  }

  void SetModel(std::shared_ptr<IModel> const& model)
  {
    AddState(TitleScreenView::Create());
    AddState(MainMenuView::Create());
    AddState(PreGameView::Create());
    AddState(OverworldView::Create());
    AddState(BattleView::Create());

    _model = model;    
  }

  std::shared_ptr<IModel> _model;  
};

std::shared_ptr<ConsoleView> ConsoleView::Create()
{
  return std::make_shared<ConsoleViewImpl>();
}

}
