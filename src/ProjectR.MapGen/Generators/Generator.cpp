#include "Generator.hpp"
#include "Extensions.hpp"
#include "ProjectR.Model/RMap.hpp"

namespace ProjectR
{
Generator::Generator(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map)
  : _minWidth(minWidth),
    _minHeight(minHeight),
    _maxWidth(maxWidth),
    _maxHeight(maxHeight),
    _map(map)
{
}

bool Generator::Generate(int row, int col, Direction dir)
{
  SetWidth(Roll(_minWidth, _maxWidth));
  SetHeight(Roll(_minHeight, _maxHeight));

  if(!CheckAvailableSpace(row, col, dir))
    return false;
  GenerateImpl(row, col, dir);
  return true;
}

bool Generator::CheckAvailableSpace(int row, int col, Direction dir)
{
  int topRow = row;
  int leftCol = col;
  GetTopLeftCorner(topRow, leftCol, dir);

  // We have to move one block away, or it's guaranteed to fail the check
  MoveInDirection(topRow, leftCol, dir);

  for(int r = topRow; r < topRow + _height; ++r)
  {
    for(int c = leftCol; c < leftCol + _width; ++c)
    {
      if(r < 0 || r >= _map->Rows() || c < 0 || c >= _map->Columns())
        return false;
      if(!(_map->Get(r, c) & Diggable))
        return false;
    }
  }
  return true;
}

void Generator::GetTopLeftCorner(int& row, int& col, Direction dir)
{
  switch(dir)
  {
  case Center:
    row -= _offsetY;
    col -= _offsetX;
    break;

  case North:
    row -= _offsetY * 2;
    col -= _offsetX;
    break;

  case South:
    col -= _offsetX;
    break;

  case East:
    row -= _offsetY;
    break;

  case West:
    row -= _offsetY;
    col -= _offsetX * 2;
    break;
  }
}

void Generator::SetWidth(int w)
{
  _width = MakeOdd(w);
  _offsetX = _width / 2.f;
}

void Generator::SetHeight(int h)
{
  _height = MakeOdd(h);
  _offsetY = _height / 2.f;
}
}
