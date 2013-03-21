#pragma once
#include <memory>
#include <string>
#include "RaceTemplate.hpp"

namespace ProjectR
{
class RaceTemplate;

class RaceTemplates
{
public:
  virtual void LoadTemplates() = 0;
  virtual RaceTemplate const& GetTemplate(std::string const& name) = 0;
  virtual RaceTemplate const& GetRandomTemplate() = 0;

  virtual ~RaceTemplates(){}
  static std::shared_ptr<RaceTemplates> Create();
};
}
