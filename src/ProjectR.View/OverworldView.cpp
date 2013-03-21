#include "OverworldView.hpp"
#include "IModel.hpp"

namespace ProjectR
{
struct OverworldViewImpl : public OverworldView
{
  OverworldViewImpl()
  {
  }

  void Run()
  {
  }
};

std::shared_ptr<OverworldView> OverworldView::Create()
{
  return std::make_shared<OverworldViewImpl>();
}
}
