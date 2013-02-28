#pragma once
#include <vector>
#include <boost/random.hpp>
#include <ctime>
#include "Direction.hpp"

namespace ProjectR
{
static boost::random::mt19937 rng(time(0));

template<class T>
static std::vector<T>& ShuffleVec(std::vector<T>& vec)
{
  int n = vec.size();
  while(n > 1)
  {
    --n;
    int k = boost::random::uniform_int_distribution<>(0, n)(rng);
    T value = vec[k];
    vec[k] = vec[n];
    vec[n] = value;
  }
  return vec;
}

static inline void MoveInDirection(int& row, int& col, Direction dir)
{
  switch(dir)
  {
  case North:
    row -= 1;
    break;

  case East:
    col += 1;
    break;

  case South:
    row += 1;
    break;

  case West:
    col -= 1;
    break;

  case Center:
    break;
  }
}

static inline int Roll(int min, int max)
{
  return boost::random::uniform_int_distribution<>(min, max)(rng);
}

static inline int Roll(int max)
{
  return boost::random::uniform_int_distribution<>(0, max)(rng);
}

static inline int MakeEven(int n)
{
  return n % 2 == 0 ? n : n + 1;
}

static inline int MakeOdd(int n)
{
  return n % 2 == 0 ? n + 1 : n;
}
}
