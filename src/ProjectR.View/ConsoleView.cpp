#include "ConsoleView.hpp"
#include "RConsole.hpp"
#include "TitleScreenView.hpp"

namespace ProjectR
{
struct ConsoleViewImpl : public ConsoleView
{
  ConsoleViewImpl()
    : _model(),
      _titleScreen(TitleScreenView::Create())
  {
    RConsole::InitializeRootConsole(1920.f / 8, 1080.f / 8);
  }

  ~ConsoleViewImpl()
  {
  }

  void Show()
  {
    GetCurrentState()->Run();
    RConsole::Draw();
  }

  void Notify()
  {
    Show();
  }

  void SetModel(std::shared_ptr<IModel> model)
  {
    AddState(_titleScreen);

    _model = model;
    _titleScreen->SetModel(model);
  }

  std::shared_ptr<IModel> _model;
  std::shared_ptr<ModelState> _titleScreen;
};

ConsoleView* ConsoleView::Create()
{
  return new ConsoleViewImpl();
}

}
