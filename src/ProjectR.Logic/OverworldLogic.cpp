#include "OverworldLogic.hpp"

namespace ProjectR
{
struct OverworldLogicImpl : public OverworldLogic
{
  OverworldLogicImpl()
  {
  }

  void Run()
  {
  }
};

std::shared_ptr<OverworldLogic> OverworldLogic::Create()
{
  return std::make_shared<OverworldLogicImpl>();
}
}
