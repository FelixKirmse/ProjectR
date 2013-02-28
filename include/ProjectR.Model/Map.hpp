#pragma once

namespace ProjectR
{
template<class T>
class Map
{
public:
  Map()
  {
  }

  inline int Columns() { return _columns; }
  inline int Rows() { return _rows; }  

  inline T& Get(int row, int col)
  {    
    return _map[row][col];
  }

private:
  int const _rows = 1000;
  int const _columns = 1000;

  T _map[1000][1000];
};
}
