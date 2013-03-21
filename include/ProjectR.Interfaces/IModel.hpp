#pragma once
#include <memory>
#include <string>


namespace ProjectR
{
class RMap;
class TitleModel;
class MenuModel;
class OverWorldModel;
class BattleModel;
class Statistics;
class PreGameModel;
class RaceTemplates;
class CharacterFactory;
class SpellFactory;
class Party;

class IModel
{
public:
  virtual std::shared_ptr<RMap> const& GetMap() const = 0;

  virtual std::shared_ptr<TitleModel> const& GetTitleModel() const = 0;
  virtual std::shared_ptr<MenuModel> const & GetMenuModel() const = 0;
  virtual std::shared_ptr<OverWorldModel> const& GetOverworldModel() const = 0;
  virtual std::shared_ptr<BattleModel> const& GetBattleModel() const = 0;
  virtual std::shared_ptr<PreGameModel> const& GetPreGameModel() const = 0;
  virtual std::shared_ptr<Statistics> const& GetStatistics() const = 0;
  virtual std::shared_ptr<RaceTemplates> const& GetRaceTemplates() const = 0;
  virtual std::shared_ptr<CharacterFactory> const& GetCharacterFactory() const = 0;
  virtual std::shared_ptr<SpellFactory> const& GetSpellFactory() const = 0;
  virtual std::shared_ptr<Party> const& GetParty() const = 0;

  virtual std::string const& GetPlayerName() const = 0;
  virtual void SetPlayerName(std::string const&) = 0;

  virtual void CommitChanges() = 0;

  virtual void LoadResources() = 0;

  virtual ~IModel() {}
};
}
