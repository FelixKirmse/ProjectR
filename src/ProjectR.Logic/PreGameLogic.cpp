#include "PreGameLogic.hpp"
#include "IModel.hpp"
#include "PreGameModel.hpp"
#include "InputBuffer.hpp"
#include "RInput.hpp"
#include "IStateMachine.hpp"

namespace ProjectR
{
struct PreGameLogicImpl : public PreGameLogic
{
  PreGameLogicImpl()
  {
  }

  void Deactivate()
  {
    Model()->GetPreGameModel()->GetInputBuffer()->Reset();
  }

  void Run()
  {
    Input()->Update();
    auto buffer = Model()->GetPreGameModel()->GetInputBuffer();
    char input = Input()->GetChar();

    if(Input()->Action(Confirm))
    {
      Model()->SetPlayerName(buffer->GetString());
      Master()->Next();
    }
    else if(Input()->Action(Back))
      buffer->RemoveChar();
    else if(Input()->Action(Cancel))
      Master()->Previous();
    else if(buffer->GetLength() < 16 && input != 0)
      buffer->AddChar(input);

    Model()->CommitChanges();
  }
};

std::shared_ptr<PreGameLogic> PreGameLogic::Create()
{
  return std::make_shared<PreGameLogicImpl>();
}
}
