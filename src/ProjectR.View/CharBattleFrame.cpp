#include "CharBattleFrame.hpp"
#include "Character.hpp"
#include "RConsole.hpp"
#include "NumberSanitizer.hpp"
#include "Stats.hpp"

namespace ProjectR
{
struct BaseBattleFrame : public CharBattleFrame
{
  BaseBattleFrame()
    : _charConsole(16, 10)
  {
    if(_root == nullptr)
      _root = RConsole::GetRootConsole();
    DrawStatics();
  }

  void DrawStatics()
  {
    _charConsole.SetBackgroundColour(Colour::black);
    _charConsole.SetForegroundColour(Colour::white);
    _charConsole.PrintString(Rectangle(1, 4, 5, 5), "Turn:\n\nHP  :\n\nMP  :");
  }

  void SetPosition(int x, int y)
  {
    _position.X = x;
    _position.Y = y;
  }

  void AssignCharacter(std::shared_ptr<Character> const& chara)
  {
    _currentChar = chara;
  }

  void Draw()
  {
    DrawBorder();

    if(_cachedName != _currentChar->GetName())
      DrawName();

    DrawTurn();
    DrawHP();

    if(_cachedMP != _currentChar->GetCurrentMP())
      DrawMP();

    _root->Blit(_charConsole, _charConsole.GetBounds(), _position.X, _position.Y);
  }

  void DrawBorder()
  {
    _charConsole.SetForegroundColour(
          _currentChar->IsMarked() && _currentChar->TakesTurn() ? Colour::orange :
                                                                  _currentChar->IsMarked() ? Colour::red :
                                                                                             _currentChar->TakesTurn() ? Colour::green :
                                                                                                                         Colour::white);

    for(int col = 0; col < _charConsole.GetWidth(); ++col)
    {
      int drawChar = col == 0 ? TCOD_CHAR_NW :
                                col == _charConsole.GetWidth() - 1 ? TCOD_CHAR_NE :
                                                                     TCOD_CHAR_HLINE;
      _charConsole.SetCharacter(col, 0, drawChar);
    }

    for(int col = 0; col < _charConsole.GetWidth(); ++col)
    {
      int drawChar = col == 0 ? TCOD_CHAR_SW :
                                col == _charConsole.GetWidth() - 1 ? TCOD_CHAR_SE :
                                                                     TCOD_CHAR_HLINE;
      _charConsole.SetCharacter(col, _charConsole.GetHeight() - 1, drawChar);
    }

    for(int row = 1; row < _charConsole.GetHeight() - 1; ++row)
    {
      _charConsole.SetCharacter(0, row, TCOD_CHAR_VLINE);
      _charConsole.SetCharacter(_charConsole.GetWidth() - 1, row, TCOD_CHAR_VLINE);
    }

    _charConsole.SetForegroundColour(Colour::white);
  }

  void DrawName()
  {
    _cachedName = _currentChar->GetName();
    _charConsole.PrintString(Rectangle(8, 1, 13, 2),"                          ", TCOD_CENTER);
    _charConsole.PrintString(Rectangle(8, 1, 13, 2), _cachedName, TCOD_CENTER);
  }

  void DrawTurn()
  {
    _charConsole.PrintString(6, 4, "    ");
    float percentage = _currentChar->GetTurnCounter() / _currentChar->GetTimeToAction();
    Colour colour(_currentChar->TakesTurn() ? 0.f : 30.f, 1.f, 1.f);
    _charConsole.SetColourControl(TCOD_COLCTRL_1, colour);

    boost::format turnFormat("%%c%.2f%%%%%%c");
    turnFormat
        % (_currentChar->TakesTurn() ? 100.f : (percentage * 100.f));
    _charConsole.PrintString(14, 4, turnFormat.str(), TCOD_RIGHT, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
  }

  virtual void DrawHP() = 0;

  virtual void DrawMP() = 0;

  RConsole _charConsole;
  std::shared_ptr<Character> _currentChar;
  Point _position;
  RConsole* _root = nullptr;
  std::string _cachedName = "";
  int _cachedMP = 0;
};

struct PlayerBattleFrame : public BaseBattleFrame
{
  void DrawHP()
  {
    _charConsole.PrintString(6, 6, "         ");
    float currentHP = _currentChar->GetCurrentHP();
    float percentage = currentHP / _currentChar->GetStats()->GetTotalStat(HP);
    Colour colour(120.f * percentage, 1.f, 1.f);
    _charConsole.SetColourControl(TCOD_COLCTRL_1, colour);

    _charConsole.PrintString(14, 6, "%c" + NumberSanitizer::Sanitize(currentHP) + "%c", TCOD_RIGHT, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
  }

  void DrawMP()
  {
    _cachedMP = _currentChar->GetCurrentMP();
    _charConsole.PrintString(6, 8, "        ");

    float percentage = _cachedMP / 200.f;
    Colour colour(205.f * percentage, 1.f, 1.f);
    _charConsole.SetColourControl(TCOD_COLCTRL_1, colour);

    boost::format mpFormat("%%c%d%%c");
    mpFormat
        % _cachedMP;
    _charConsole.PrintString(14, 8, mpFormat.str(), TCOD_RIGHT, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
  }
};

struct EnemyBattleFrame : public BaseBattleFrame
{
  void DrawHP()
  {
    _charConsole.PrintString(6, 6, "         ");
    float currentHP = _currentChar->GetCurrentHP();
    float percentage = currentHP / _currentChar->GetStats()->GetTotalStat(HP);
    Colour colour(120.f * percentage, 1.f, 1.f);
    _charConsole.SetColourControl(TCOD_COLCTRL_1, colour);

    _charConsole.PrintString(14, 6, "%c" + (boost::format("%.2f%%%%") % (percentage * 100.f)).str() + "%c", TCOD_RIGHT, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
  }

  void DrawMP()
  {
    _cachedMP = _currentChar->GetCurrentMP();
    _charConsole.PrintString(6, 8, "        ");

    float percentage = _cachedMP / _currentChar->GetStats()->GetTotalStat(MP);
    Colour colour(205.f * percentage, 1.f, 1.f);
    _charConsole.SetColourControl(TCOD_COLCTRL_1, colour);

    boost::format mpFormat("%%c%.2f%%%%%%c");
    mpFormat
        % (percentage * 100.f);
    _charConsole.PrintString(14, 8, mpFormat.str(), TCOD_RIGHT, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
  }
};

std::shared_ptr<CharBattleFrame> CharBattleFrame::CreateFrameForEnemyChar()
{
  return std::make_shared<EnemyBattleFrame>();
}

std::shared_ptr<CharBattleFrame> CharBattleFrame::CreateFrameForPlayerChar()
{
  return std::make_shared<PlayerBattleFrame>();
}
}
