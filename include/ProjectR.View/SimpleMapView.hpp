#pragma once
#include "IView.hpp"
#include "IObserver.hpp"

namespace ProjectR
{
class SimpleMapView : public IView, public IObserver
{
public:
  SimpleMapView();
  ~SimpleMapView();

  void Show();
  void SetModel(std::shared_ptr<IModel> model);
  void Notify();

private:
  class SimpleMapViewImpl* _;
};

}
