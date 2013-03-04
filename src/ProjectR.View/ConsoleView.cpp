#include "ConsoleView.hpp"
#include "RConsole.hpp"
#include "TitleScreenView.hpp"

namespace ProjectR
{
struct ConsoleViewImpl : public ConsoleView
{
  ConsoleViewImpl()
    : _model()
  {
    RConsole::InitializeRootConsole(1920.f / 8, 1080.f / 8);
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

    _model = model;    
  }

  std::shared_ptr<IModel> _model;  
};

std::shared_ptr<ConsoleView> ConsoleView::Create()
{
  return std::make_shared<ConsoleViewImpl>();
}

}
