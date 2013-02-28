#pragma once
#include "IModel.hpp"
#include "Observeable.hpp"

namespace ProjectR
{
class RModel : public IModel, public Observeable
{
public:
  RModel();
  ~RModel();

  std::shared_ptr<RMap> GetMap() const;

  std::shared_ptr<TitleModel> GetTitleModel() const;
  std::shared_ptr<MenuModel> GetMenuModel() const;
  std::shared_ptr<OverWorldModel> GetOverworldModel() const;
  std::shared_ptr<BattleModel> GetBattleModel() const;

  void CommitChanges();

  void LoadResources();

private:
  class RModelImpl* _;
};
}
