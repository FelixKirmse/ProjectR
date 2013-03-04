#pragma once
#include "IModel.hpp"
#include "Observeable.hpp"

namespace ProjectR
{
class RModel : public IModel, public Observeable
{
public:
  static std::shared_ptr<RModel> Create();
  virtual ~RModel() {}
};
}
