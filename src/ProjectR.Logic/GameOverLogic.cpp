#include "GameOverLogic.hpp"
#include "IModel.hpp"
#include "RInput.hpp"

namespace ProjectR
{
struct GameOverImpl : public GameOverLogic
{
  void Run()
  {
    Model()->CommitChanges();
    do
    {
      Input()->Update();
    }while(!Input()->Action(Confirm));
    _gameOver = true;
  }

  bool GameOver()
  {
    bool result = _gameOver;
    if(result)
      _gameOver = false;
    return result;
  }

  bool _gameOver = false;
};

std::shared_ptr<GameOverLogic> GameOverLogic::Create()
{
  return std::make_shared<GameOverImpl>();
}
}
