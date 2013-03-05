#include "ProjectR.hpp"
#include "ProjectR.Model/StateMachineSynchronizer.hpp"
#include <memory>
#include "ProjectR.Model/RModel.hpp"
#include "ProjectR.View/ConsoleView.hpp"
#include "RConsole.hpp"
#include "RLogic.hpp"
#include "ModelState.hpp"

namespace ProjectR
{
static bool _exitGame(false);

struct ProjectRImpl : ProjectR
{
  ProjectRImpl()
    : _stateSyncer(new StateMachineSynchronizer()),
      _model(RModel::Create()),
      _view(ConsoleView::Create()),
      _logic(RLogic::Create())
  {
    ModelState::SetModel(_model);    
  }

  void SetupGameStructure()
  {
    _stateSyncer->AddSynchronizeable(_view);
    _stateSyncer->AddSynchronizeable(_logic);
    _view->SetModel(_model);
    _logic->SetModel(_model);
    _model->AddObserver(_view);
    _stateSyncer->Sync(0);
  }

  void RunGame()
  {    
    _model->CommitChanges();
    do
    {     
      _logic->RunCurrentState();
    }while(!_exitGame && !TCODConsole::isWindowClosed());
  }

  std::shared_ptr<StateMachineSynchronizer> _stateSyncer;
  std::shared_ptr<RModel> _model;
  std::shared_ptr<ConsoleView> _view;
  std::shared_ptr<RLogic> _logic;
};

std::shared_ptr<ProjectR> ProjectR::Create()
{
  return std::make_shared<ProjectRImpl>();
}

void ProjectR::Exit()
{
  _exitGame = true;
}
}
