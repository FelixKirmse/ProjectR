#include "RModel.hpp"
#include "RMap.hpp"
#include "TitleModel.hpp"
#include "MenuModel.hpp"
#include "OverWorldModel.hpp"
#include "BattleModel.hpp"
#include "Statistics.hpp"
#include "PreGameModel.hpp"
#include "RaceTemplates.hpp"
#include "CharacterFactory.hpp"
#include "SpellFactory.hpp"

namespace ProjectR
{

struct RModelImpl : public RModel
{
  RModelImpl()
    : _map(new RMap()),
      _titleModel(new TitleModel()),
      _menuModel(new MenuModel()),
      _preGameModel(PreGameModel::Create()),
      _overWorldModel(new OverWorldModel()),
      _battleModel(new BattleModel()),
      _statistics(Statistics::Create()),
      _raceTemplates(RaceTemplates::Create()),
      _charFactory(CharacterFactory::Create(*this)),
      _spellFactory(SpellFactory::Create(*this))
  {
  }

  std::shared_ptr<RMap> const& GetMap() const
  {
    return _map;
  }

  std::shared_ptr<TitleModel> const& GetTitleModel() const
  {
    return _titleModel;
  }

  std::shared_ptr<MenuModel> const& GetMenuModel() const
  {
    return _menuModel;
  }

  std::shared_ptr<OverWorldModel> const& GetOverworldModel() const
  {
    return _overWorldModel;
  }

  std::shared_ptr<BattleModel> const& GetBattleModel() const
  {
    return _battleModel;
  }

  std::shared_ptr<Statistics> const& GetStatistics() const
  {
    return _statistics;
  }

  std::shared_ptr<PreGameModel> const& GetPreGameModel() const
  {
    return _preGameModel;
  }

  std::shared_ptr<RaceTemplates> const& GetRaceTemplates() const
  {
    return _raceTemplates;
  }

  std::string const& GetPlayerName() const
  {
    return _playerName;
  }

  std::shared_ptr<CharacterFactory> const& GetCharacterFactory() const
  {
    return _charFactory;
  }

  std::shared_ptr<SpellFactory> const& GetSpellFactory() const
  {
    return _spellFactory;
  }

  void SetPlayerName(std::string const& playerName)
  {
    _playerName = playerName;
  }

  void LoadResources()
  {
    _spellFactory->LoadSpells();
    _raceTemplates->LoadTemplates();
    _charFactory->LoadCharacters();
  }

  void CommitChanges()
  {
    NotifyObservers();
  }

  std::shared_ptr<RMap> _map;
  std::shared_ptr<TitleModel> _titleModel;
  std::shared_ptr<MenuModel> _menuModel;
  std::shared_ptr<PreGameModel> _preGameModel;
  std::shared_ptr<OverWorldModel> _overWorldModel;
  std::shared_ptr<BattleModel> _battleModel;
  std::shared_ptr<Statistics> _statistics;
  std::shared_ptr<RaceTemplates> _raceTemplates;
  std::shared_ptr<CharacterFactory> _charFactory;
  std::shared_ptr<SpellFactory> _spellFactory;
  std::string _playerName;
};

std::shared_ptr<RModel> RModel::Create()
{
  return std::make_shared<RModelImpl>();
}

}
