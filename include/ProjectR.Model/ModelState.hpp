#pragma once
#include "IState.hpp"

namespace ProjectR
{
class IModel;
class ModelState : public IState
{
public:
  inline void SetModel(std::shared_ptr<IModel> model) { _model = model; }
  inline std::shared_ptr<IModel> Model(){ return _model; }

private:
  std::shared_ptr<IModel> _model;

};
}
