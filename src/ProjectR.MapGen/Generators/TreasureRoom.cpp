#include "TreasureRoom.hpp"
#include "ProjectR.Model/RMap.hpp"
#include "ProjectR.Model/RandomContainer.hpp"
#include "Extensions.hpp"
#include <cmath>

namespace ProjectR
{
// Could be private members, but don't want to have Header dependency on RandomContainer.
// Besides, we only need one instance of each anyways
static RandomContainer<int> _rarities =
{
  { Uncommon, 600 },
  { Rare, 200 },
  { Epic, 50 },
  { Legendary, 10 },
  { Artifact, 1 },
};

static RandomContainer<int> _sizes =
{
  { Normal, 20 },
  { Small, 75 },
  { Big, 4 },
  { Grand, 1 },
};

TreasureRoom::TreasureRoom(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map)
  : Generator(minWidth, minHeight, maxWidth, maxHeight, map)
{  
}

void TreasureRoom::GenerateImpl(int row, int col, Direction dir)
{
  int topRow = row;
  int leftCol = col;
  GetTopLeftCorner(topRow, leftCol, dir);
  int maxRow = topRow + GetHeight();
  int maxCol = leftCol + GetWidth();

  for(int r = topRow; r < maxRow; ++r)
  {
    for(int c = leftCol; c < maxCol; ++c)
    {
      auto& cell = Map()->Get(r, c);
      if(r == topRow || c == leftCol || r == maxRow - 1 || c == maxCol - 1)
        cell = Wall | Important;
      else
        cell = Floor;
    }
  }

  int treasureCount = sqrt(GetWidth() * GetHeight());

  for(int i = 0; i < treasureCount; ++i)
  {
    int chestRow;
    int chestCol;
    do
    {
      chestRow = Roll(topRow + 1, maxRow - 2);
      chestCol = Roll(leftCol + 1, maxCol - 2);
    }while(Map()->Get(chestRow, chestCol) & Chest);
    auto& cell = Map()->Get(chestRow, chestCol);
    cell |= Chest | _sizes.Get() | _rarities.Get();
  }

  if(dir != Center)
    Map()->Get(row, col) = Door | Locked;
}
}
