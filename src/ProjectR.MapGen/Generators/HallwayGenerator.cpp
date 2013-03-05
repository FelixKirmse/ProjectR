#include "HallwayGenerator.hpp"
#include "ProjectR.Model/RMap.hpp"

namespace ProjectR
{
HallwayGenerator::HallwayGenerator(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map)
  : Generator(minWidth, minHeight, maxWidth, maxHeight, map)
{
}

void HallwayGenerator::GenerateImpl(int row, int col, Direction dir)
{
  int topRow = row;
  int leftCol = col;

  int length = GetWidth() > GetHeight() ? GetWidth() : GetHeight();

  if(dir & (West | East))
  {
    SetHeight(3);
    SetWidth(length);
  }


  if(dir & (South | North))
  {
    SetWidth(3);
    SetHeight(length);
  }


  GetTopLeftCorner(topRow, leftCol, dir);

  int maxRow = topRow + GetHeight();
  int maxCol = leftCol + GetWidth();
  for(int r = topRow; r < maxRow; ++r)
  {
    for(int c = leftCol; c < maxCol; ++c)
    {
      auto& cell = Map()->Get(r, c);
      if(r == row && c == col)
      {
        if(cell & Important)
          cell = Door | Important | Locked;
        else
          cell = Floor | Corridor;
      }
      else if(r == topRow || c == leftCol || r == maxRow - 1 || c == maxCol -1)
        cell = Wall | Corridor;
      else
        cell = Floor | Corridor;
    }
  }

}
}
