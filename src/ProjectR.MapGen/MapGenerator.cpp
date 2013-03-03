#include "MapGenerator.hpp"
#include "ProjectR.Model/RMap.hpp"
#include "ProjectR.Model/RandomContainer.hpp"
#include "IGenerator.hpp"
#include <boost/unordered_map.hpp>
#include <vector>
#include "Extensions.hpp"
#include "RoomGenerator.hpp"
#include "HallwayGenerator.hpp"
#include "DrunkDigger.hpp"
#include "TreasureRoom.hpp"

namespace ProjectR
{
struct MapGenImpl : public MapGenerator
{
  MapGenImpl(std::shared_ptr<RMap> map)
    : _map(map),
      Rows(map->Rows()),
      Cols(map->Columns()),
      _featureTarget(0),
      _roomGen(new RoomGenerator(5, 5, 15, 10, _map)),
      _corridorGen(new HallwayGenerator(20, 20, 50, 50, _map)),
      _drunkDigger(new DrunkDigger(50, 50, 100, 100, _map)),
      _treasureRoom(new TreasureRoom(5, 5, 13, 13, _map)),
      _generators()
  {
    _generators.Add(_roomGen, 60);
    _generators.Add(_corridorGen, 15);
    _generators.Add(_drunkDigger, 120);
    _generators.Add(_treasureRoom, 2);
  }

  ~MapGenImpl()
  {
    delete _roomGen;
    delete _corridorGen;
    delete _drunkDigger;
    delete _treasureRoom;
  }

  std::shared_ptr<RMap> _map;
  int const Rows;
  int const Cols;
  int _featureTarget;
  IGenerator* _roomGen;
  IGenerator* _corridorGen;
  IGenerator* _drunkDigger;
  IGenerator* _treasureRoom;
  RandomContainer<IGenerator*> _generators;
  std::vector<Direction>& _directions = GetDirections();
  boost::unordered::unordered_map<Direction, Direction> _oppositeDirection =
  {
    { North, South },
    { East, West },
    { South, North },
    { West, East },
    { Center, Center }
  };


  void PrepareMap()
  {
    for(int row = 0; row < Rows; ++row)
    {
      for(int col = 0; col < Cols; ++col)
      {
        if(row == 0 || col == 0 || row == Rows - 1 || col == Cols - 1)
          _map->Get(row, col) = Border;
        else
          _map->Get(row, col) = Diggable;
      }
    }
    _generators.Get()->Generate(Rows / 2.f, Cols / 2.f, Center);
    _map->RecalculateHeatZone();
  }

  bool ValidCell(int row, int col, Direction& direction)
  {
    direction = Center;
    auto& cell = _map->Get(row, col);

    if(!(cell & Wall))
      return false;

    ShuffleVec(_directions);

    for(auto dir : _directions)
    {
      direction = dir;
      int checkRow = row;
      int checkCol = col;
      MoveInDirection(checkRow, checkCol, dir);
      int checkRowOpp = row;
      int checkColOpp = col;
      MoveInDirection(checkRowOpp, checkColOpp, _oppositeDirection[dir]);

      if(_map->Get(checkRow, checkCol) & Diggable &&
         _map->Get(checkRowOpp, checkColOpp) & Walkable)
        return true;
    }
    return false;
  }

  void GenerateFeatures()
  {
    for(int i = 0; i < _featureTarget; ++i)
    {
      int row = 0;
      int col = 0;
      Direction dir;
      Rectangle heatZone = _map->HeatZone();
      do
      {
        do
        {
          row = Roll(heatZone.Top(), heatZone.Bottom());
          col = Roll(heatZone.Left(), heatZone.Right());
        }while(!ValidCell(row, col, dir));
      }while(!_generators.Get()->Generate(row, col, dir));
      _map->RecalculateHeatZone();
    }
  }

  void GenerateMap(int level)
  {
    _featureTarget = level * 2 + Roll(5, 15);
    PrepareMap();
    GenerateFeatures();
  }
};

MapGenerator* MapGenerator::Create(std::shared_ptr<RMap> map)
{
  return new MapGenImpl(map);
}
}
