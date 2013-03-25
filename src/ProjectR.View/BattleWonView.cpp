#include "BattleWonView.hpp"

namespace ProjectR
{
struct BattleWonViewImpl : public BattleWonView
{
  void Run()
  {
  }
};

std::shared_ptr<BattleWonView> BattleWonView::Create()
{
  return std::make_shared<BattleWonViewImpl>();
}
}
