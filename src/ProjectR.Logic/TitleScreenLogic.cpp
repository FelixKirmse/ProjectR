#include "TitleScreenLogic.hpp"
#include <libtcod/libtcod.hpp>
#include "IModel.hpp"
#include "ProjectR.hpp"
#include "RInput.hpp"
#include "IStateMachine.hpp"

namespace ProjectR
{
struct TitleScreenLogicImpl : public TitleScreenLogic
{
  TitleScreenLogicImpl()
  {
  }  

  void Run()
  {   
    Input()->Update();
    if(Input()->Action(Cancel))
    {
      ProjectR::Exit();
    }
    else if(Input()->Action(Confirm))
    {
      Master()->Next();
    }
    Model()->CommitChanges();
  }

};


std::shared_ptr<TitleScreenLogic> TitleScreenLogic::Create()
{
  return std::make_shared<TitleScreenLogicImpl>();
}
}
