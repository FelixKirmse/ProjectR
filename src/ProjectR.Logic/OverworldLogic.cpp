#include "OverworldLogic.hpp"
#include "IStateMachine.hpp"

namespace ProjectR
{
struct OverworldLogicImpl : public OverworldLogic
{
  OverworldLogicImpl()
  {
  }

  void Run()
  {
    Master()->Next();
  }
};

std::shared_ptr<OverworldLogic> OverworldLogic::Create()
{
  return std::make_shared<OverworldLogicImpl>();
}
}
