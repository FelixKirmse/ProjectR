#include "BattleLogDrawer.hpp"
#include "IModel.hpp"
#include "BattleLog.hpp"
#include "BattleModel.hpp"
#include "RConsole.hpp"
#include <sstream>

namespace ProjectR
{
struct LogDrawer : public BattleLogDrawer
{
  LogDrawer()
    : _logConsole(37, 21),
      LogArea(1, 3, _logConsole.GetWidth(), _logConsole.GetHeight() - 3)
  {
  }

  void SetPosition(int x, int y)
  {
    _position.X = x;
    _position.Y = y;
  }

  void Activate()
  {
    _log = Model()->GetBattleModel()->GetBattleLog();
    _root = RConsole::GetRootConsole();
    _log->ClearLog();
  }

  void Run()
  {
    int fetchCount = 5;

    do
    {
      _logConsole.Clear();
      _logConsole.DrawBorder();
      _logConsole.SetColourControl(TCOD_COLCTRL_1, Colour::red);
      _logConsole.PrintString(1, 1, "%cBattlelog:%c", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
      auto const log = _log->GetLastEntries(fetchCount);
      _logStream.str("");
      _logStream.clear();

      for(auto logEntry : log)
      {
        _logStream << logEntry << std::endl << std::endl;
      }
      --fetchCount;
    }
    while(_logConsole.PrintString(LogArea, _logStream.str()) > MaxLogLines);
    _root->Blit(_logConsole, _logConsole.GetBounds(), _position.X, _position.Y);
  }

  std::shared_ptr<BattleLog> _log = nullptr;
  RConsole _logConsole;
  Point _position;
  RConsole* _root;
  std::stringstream _logStream;
  int const MaxLogLines = 18;
  Rectangle const LogArea;

};

std::shared_ptr<BattleLogDrawer> BattleLogDrawer::Create()
{
  return std::make_shared<LogDrawer>();
}
}
