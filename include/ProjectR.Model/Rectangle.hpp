#pragma once

namespace ProjectR
{
struct Point
{
  Point(int x, int y) : X(x), Y(y){}
  Point() : Point(0,0){}
  int X;
  int Y;

  bool operator==(Point const& other) const
  {
    return X == other.X && Y == other.Y;
  }
};

struct Rectangle
{
  int X;
  int Y;
  int Width;
  int Height;

  Rectangle(int x, int y, int width, int height)
    : X(x), Y(y), Width(width), Height(height)
  {
  }

  Rectangle()
  : X(0), Y(0), Width(0), Height(0)
  {
  }

  inline int Bottom() const { return Y + Height; }
  inline Point Center() const { return Point(X + Width / 2, Y + Height / 2); }
  inline int Left() const { return X; }
  inline int Right() const { return X + Width; }
  inline int Top() const { return Y; }

  inline int Contains(int x, int y) const { return X <= x && x < X + Width && Y <= y && y < Y + Height; }
};
}
