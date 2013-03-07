#include "PreGameView.hpp"
#include "RConsole.hpp"
#include "IModel.hpp"
#include "PreGameModel.hpp"
#include "InputBuffer.hpp"

namespace ProjectR
{
struct PreGameViewImpl : public PreGameView
{
  PreGameViewImpl()
    : _text("Name: "),
      _printOffset(_text.size()),
      _console(20, 1)
  {
    _console.SetBackgroundColour(Colour::black);
    _console.SetForegroundColour(Colour::white);
  }

  void Run()
  {
    auto buffer = Model()->GetPreGameModel()->GetInputBuffer();
    auto rootConsole = RConsole::GetRootConsole();
    rootConsole->Clear();
    _console.Clear();
    _console.PrintString(0, 0, _text);
    auto string = buffer->GetString();
    _console.PrintString(_printOffset, 0, string);
    rootConsole->Blit(_console, _console.GetBounds(),
                      rootConsole->GetWidth() / 2 - string.size() / 2,
                      rootConsole->GetHeight() / 2);
  }

  std::string const _text;
  int const _printOffset;
  RConsole _console;
};

std::shared_ptr<PreGameView> PreGameView::Create()
{
  return std::make_shared<PreGameViewImpl>();
}
}
