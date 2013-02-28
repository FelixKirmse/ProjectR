#include "DrunkDigger.hpp"
#include "ProjectR.Model/RMap.hpp"
#include "Extensions.hpp"

namespace ProjectR
{
DrunkDigger::DrunkDigger(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map)
  : Generator(minWidth, minHeight, maxWidth, maxHeight, map)
{
}

struct Digger
{
  Digger(int row, int col, int goal, Rectangle const& area, RMap *map);

  void Dig();

  static void DigCell(int row, int col);

  int Row;
  int Col;
  int DigGoal;
  Rectangle const DigArea;
  static RMap* Map;

private:
  bool CanMove(int row, int col);
  bool CanDig();
  void DigOut();

  int _digged;
};


void DrunkDigger::GenerateImpl(int row, int col, Direction dir)
{
  int topRow = row;
  int leftCol = col;
  GetTopLeftCorner(topRow, leftCol, dir);

  int goalRow = row;
  int goalCol = col;
  MoveInDirection(goalRow, goalCol, dir);

  Rectangle digArea(leftCol + 1, topRow + 1, GetWidth() - 2, GetHeight() - 2);
  Digger digger(goalRow, goalCol, (digArea.Width * digArea.Height) / 25.f, digArea, Map().get());
  auto& cell = Map()->Get(row, col);
  cell = cell & Important ? Door : Floor;
  Digger::DigCell(row, col);
  digger.Dig();
}

RMap* Digger::Map;

Digger::Digger(int row, int col, int goal, Rectangle const& area, RMap* map)
  : Row(row), Col(col), DigGoal(goal), DigArea(area), _digged(0)
{
  Map = map;
}

void Digger::Dig()
{
  DigOut();
  do
  {
    Direction dir = ShuffleVec(GetDirections())[0];
    int nextRow = Row;
    int nextCol = Col;
    MoveInDirection(nextRow, nextCol, dir);
    if(!CanMove(nextRow, nextCol))
      continue;

    Row = nextRow;
    Col = nextCol;

    if(!CanDig())
      continue;

    DigOut();
    ++_digged;
  }while(_digged < DigGoal);
}

inline void Digger::DigCell(int row, int col)
{
  auto& cell = Map->Get(row, col);
  if(cell & Diggable)
    cell = Wall;
}



inline bool Digger::CanMove(int row, int col) { return DigArea.Contains(col, row); }
inline bool Digger::CanDig() { return Map->Get(Row, Col) & (Diggable | Wall); }
inline void Digger::DigOut()
{
  Map->Get(Row, Col) = Floor;
  DigCell(Row, Col + 1);
  DigCell(Row, Col - 1);
  DigCell(Row + 1, Col);
  DigCell(Row - 1, Col);
}
}
