#pragma once

namespace ProjectR
{
class ProjectR
{
public:
  virtual void SetupGameStructure() = 0;
  virtual void RunGame() = 0;
  static ProjectR* Create();

  virtual ~ProjectR() {}
};
}
