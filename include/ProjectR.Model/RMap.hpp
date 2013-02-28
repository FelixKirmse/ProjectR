#pragma once
#include "Map.hpp"
#include "RCell.hpp"
#include "Rectangle.hpp"

namespace ProjectR
{
class RMap : public Map<int>
{
public:
  RMap();

  inline Rectangle HeatZone() { return _heatZone; }
  void RecalculateHeatZone();

private:
  Rectangle _heatZone;
};
}
