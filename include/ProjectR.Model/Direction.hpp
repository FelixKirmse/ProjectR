#pragma once
#include <vector>

namespace ProjectR
{
enum Direction
{
  North,
  East,
  South,
  West,
  Center
};

static inline std::vector<Direction>& GetDirections()
{
  static std::vector<Direction> directions = { North, East, South, West, Center };
  return directions;
}

}
