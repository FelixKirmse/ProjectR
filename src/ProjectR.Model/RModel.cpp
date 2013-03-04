#include "RModel.hpp"
#include "RMap.hpp"
#include "TitleModel.hpp"
#include "MenuModel.hpp"
#include "OverWorldModel.hpp"
#include "BattleModel.hpp"

namespace ProjectR
{

struct RModelImpl : public RModel
{
  RModelImpl()
    : _map(new RMap()),
      _titleModel(new TitleModel()),
      _menuModel(new MenuModel()),
      _overWorldModel(new OverWorldModel()),
      _battleModel(new BattleModel())
  {
  }

  std::shared_ptr<RMap> GetMap() const
  {
    return _map;
  }

  std::shared_ptr<TitleModel> GetTitleModel() const
  {
    return _titleModel;
  }

  std::shared_ptr<MenuModel> GetMenuModel() const
  {
    return _menuModel;
  }

  std::shared_ptr<OverWorldModel> GetOverworldModel() const
  {
    return _overWorldModel;
  }

  std::shared_ptr<BattleModel> GetBattleModel() const
  {
    return _battleModel;
  }

  void LoadResources()
  {
  }

  void CommitChanges()
  {
    NotifyObservers();
  }

  std::shared_ptr<RMap> _map;
  std::shared_ptr<TitleModel> _titleModel;
  std::shared_ptr<MenuModel> _menuModel;
  std::shared_ptr<OverWorldModel> _overWorldModel;
  std::shared_ptr<BattleModel> _battleModel;
};

std::shared_ptr<RModel> RModel::Create()
{
  return std::make_shared<RModelImpl>();
}

}
