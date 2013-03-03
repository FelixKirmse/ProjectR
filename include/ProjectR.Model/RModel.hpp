#pragma once
#include "IModel.hpp"
#include "Observeable.hpp"

namespace ProjectR
{
class RModel : public IModel, public Observeable
{
public:
  static RModel* Create();
  virtual ~RModel() {}
};
}
