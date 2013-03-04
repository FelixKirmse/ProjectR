#include "TitleScreenLogic.hpp"
#include <libtcod/libtcod.hpp>
#include "MapGenerator.hpp"
#include "IModel.hpp"
#include "ProjectR.hpp"
#include "RInput.hpp"

namespace ProjectR
{
struct TitleScreenLogicImpl : public TitleScreenLogic
{
  TitleScreenLogicImpl()
  {
  }

  void Run()
  {
    auto mapGen(MapGenerator::Create(Model()->GetMap()));

    mapGen->GenerateMap(100);
    Model()->CommitChanges();

    Input()->Update();
    if(Input()->Action(Cancel))
    {
      ProjectR::Exit();
    }
  }
};

std::shared_ptr<TitleScreenLogic> TitleScreenLogic::Create()
{
  return std::make_shared<TitleScreenLogicImpl>();
}
}
