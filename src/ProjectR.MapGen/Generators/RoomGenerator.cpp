#include "RoomGenerator.hpp"
#include "ProjectR.Model/RMap.hpp"

namespace ProjectR
{
RoomGenerator::RoomGenerator(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map)
  : Generator(minWidth, minHeight, maxWidth, maxHeight, map)
{
}

void RoomGenerator::GenerateImpl(int row, int col, Direction dir)
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
      {
        if(cell & Wall && !(cell & Important) && !((r == topRow && c ==leftCol) || (r == topRow && c == maxCol - 1) || (r == maxRow - 1 && c ==leftCol) || (r == maxRow - 1 && c == maxCol - 1)))
          cell = Floor;
        else
          cell = Wall | Important;
      }
      else
        cell = Floor;
    }
  }

  auto& cell = Map()->Get(row, col);
  if(cell & Wall)
    cell = Door | Locked;
}
}
