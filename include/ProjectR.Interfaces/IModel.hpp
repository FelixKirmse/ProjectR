#pragma once
#include <memory>

namespace ProjectR
{
class RMap;
class TitleModel;
class MenuModel;
class OverWorldModel;
class BattleModel;

class IModel
{
public:
  virtual std::shared_ptr<RMap> GetMap() const = 0;

  virtual std::shared_ptr<TitleModel> GetTitleModel() const = 0;
  virtual std::shared_ptr<MenuModel> GetMenuModel() const = 0;
  virtual std::shared_ptr<OverWorldModel> GetOverworldModel() const = 0;
  virtual std::shared_ptr<BattleModel> GetBattleModel() const = 0;

  virtual void CommitChanges() = 0;

  virtual void LoadResources() = 0;

  virtual ~IModel() {}
};
}
