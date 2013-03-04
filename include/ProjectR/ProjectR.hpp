#pragma once
#include <memory>

namespace ProjectR
{
class ProjectR
{
public:
  virtual void SetupGameStructure() = 0;
  virtual void RunGame() = 0;
  static std::shared_ptr<ProjectR> Create();
  static void Exit();

  virtual ~ProjectR() {}
};
}
