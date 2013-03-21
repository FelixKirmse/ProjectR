#include "BattleView.hpp"
#include "IModel.hpp"

namespace ProjectR
{
struct BattleViewImpl : public BattleView
{
  BattleViewImpl()
  {
  }

  void Run()
  {
  }
};

std::shared_ptr<BattleView> BattleView::Create()
{
  return std::make_shared<BattleViewImpl>();
}
}
