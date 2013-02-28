#include "RMap.hpp"

namespace ProjectR
{
RMap::RMap()
{
}

void RMap::RecalculateHeatZone()
{
  int lowestX = Columns();
  int lowestY = Rows();
  int highestX = 0;
  int highestY = 0;

  // HeatZone may not be bigger than map + Boundary
  for(int row = 2; row < Rows() - 1; ++row)
  {
    for(int col = 2; col < Columns() - 2; ++col)
    {
      if(!(Get(row, col) & Wall))
        continue;

      if(col < lowestX)
        lowestX = col - 1;
      if(row < lowestY)
        lowestY = row - 1;
      if(col > highestX)
        highestX = col + 1;
      if(row > highestY)
        highestY = row + 1;
    }
  }
  _heatZone = Rectangle(lowestX, lowestY, highestX - lowestX + 1, highestY - lowestY + 1);
}
}
