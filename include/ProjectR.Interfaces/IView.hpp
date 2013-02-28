#pragma once
#include <memory>

namespace ProjectR
{
class IModel;

class IView
{
public:
  virtual void Show() = 0;
  virtual void SetModel(std::shared_ptr<IModel> model) = 0;

  virtual ~IView() {}
};

}
