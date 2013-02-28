#include <iostream>
#include "ProjectR.MapGen/MapGenerator.hpp"
#include "ProjectR.Model/RModel.hpp"
#include "ProjectR.View/SimpleMapView.hpp"

int main(int argc, char** argv)
{
  using namespace ProjectR;

  std::shared_ptr<RModel> model(new RModel());
  std::shared_ptr<SimpleMapView> view(new SimpleMapView());
  view->SetModel(model);
  model->AddObserver(view);
  MapGenerator mapGen(model->GetMap());
  mapGen.GenerateMap(1);
  model->CommitChanges();

  return 0;
}
