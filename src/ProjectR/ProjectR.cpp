#include "ProjectR.hpp"
#include "ProjectR.Model/StateMachineSynchronizer.hpp"
#include <memory>
#include "ProjectR.MapGen/MapGenerator.hpp"
#include "ProjectR.Model/RModel.hpp"
#include "ProjectR.View/ConsoleView.hpp"
#include "RConsole.hpp"
#include "libtcod/libtcod.hpp"

namespace ProjectR
{
struct ProjectRImpl : ProjectR
{
  ProjectRImpl()
    : _stateSyncer(new StateMachineSynchronizer()),
      _model(RModel::Create()),
      _view(ConsoleView::Create())
  {
  }

  void SetupGameStructure()
  {
    _stateSyncer->AddSynchronizeable(_view);
    _view->SetModel(_model);
    _model->AddObserver(_view);
  }

  void RunGame()
  {
    MapGenerator* mapGen(MapGenerator::Create(_model->GetMap()));
    TCOD_key_t key;
    do
    {
      mapGen->GenerateMap(10);
      _model->CommitChanges();
      TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, 0, true);
    }while(key.vk == TCODK_ENTER);

    delete mapGen;
  }

  std::shared_ptr<StateMachineSynchronizer> _stateSyncer;
  std::shared_ptr<RModel> _model;
  std::shared_ptr<ConsoleView> _view;
};

ProjectR* ProjectR::Create()
{
  return new ProjectRImpl();
}
}
